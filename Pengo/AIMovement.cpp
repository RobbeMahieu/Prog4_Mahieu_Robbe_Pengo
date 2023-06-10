#include "AIMovement.h"
#include "MoveCommand.h"
#include <GameTime.h>
#include "EnemyState.h"

using namespace pengo;

AIMovement::AIMovement(engine::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_MovementOptions{}
	, m_CurrentOption{ nullptr }
	, m_pCollider{ m_pOwner->GetComponent<CollisionComponent>() }
	, m_RandomEngine{ std::random_device{}() }
	, m_RandomNumber{0,10}
	, m_FallbackOption{ std::make_unique<MoveCommand>(pOwner, glm::vec2{ 0,0 }, speed) }
	, m_pState{ new Turning(this) }
	, m_pKilled{}
{
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ 0,-1 }, speed)));
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ 0,1 }, speed)));
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ 1,0 }, speed)));
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ -1,0 }, speed)));

	m_CurrentOption = m_MovementOptions[0].second.get();

	m_pCollider->OnCollision.AddObserver(this);
}

AIMovement::~AIMovement() {
	delete m_pState;
}

void AIMovement::Update() {

	auto state = m_pState->Update();
	TransitionTo(state);
}

void AIMovement::OnNotify(CollisionComponent* other) {
	auto state = m_pState->HandleCollision(other);
	TransitionTo(state);
}

void AIMovement::UpdateOptions(){

	for (DirectionOption& option : m_MovementOptions) {

		glm::vec4 bounds{ m_pCollider->GetBounds() };
		glm::vec2 direction{ option.second->GetDirection() };


		// Move in the desired direction to check if something is in the way
		bounds.x += direction.x * 2;
		bounds.y += direction.y * 2;

		CollisionHit hitResult{ CollisionComponent::CheckCollision(bounds, { m_pCollider }) };

		// Only account for static/movable collision
		option.first = (hitResult.hit && (hitResult.collider->GetLayer() == CollisionLayer::STATIC || hitResult.collider->GetLayer() == CollisionLayer::DYNAMIC));

	}
}

void AIMovement::TransitionTo(EnemyState* state) {
	if (state && state != m_pState) {
		delete m_pState;
		m_pState = state;
		m_pState->OnEnter();
	}
}