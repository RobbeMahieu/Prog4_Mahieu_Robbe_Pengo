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
	, m_CanMove{ true }
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

	const auto state = m_pState->Update();
	TransitionTo(state);
}

void AIMovement::OnNotify(CollisionComponent* other) {
	const auto state = m_pState->HandleCollision(other);
	TransitionTo(state);
}

void AIMovement::UpdateOptions(){

	for (DirectionOption& option : m_MovementOptions) {

		const glm::vec2 direction{ option.second->GetDirection() };

		glm::vec3 pos{ m_pOwner->GetLocalPosition() };
		pos.x += direction.x * 2;
		pos.y += direction.y * 2;
		m_pOwner->SetLocalPosition(pos);

		// Only account for static/movable collision
		const CollisionHit hitResult{ m_pCollider->CheckCollision({}, {CollisionLayer::STATIC, CollisionLayer::DYNAMIC}) };

		pos.x -= direction.x * 2;
		pos.y -= direction.y * 2;
		m_pOwner->SetLocalPosition(pos);

		option.first = hitResult.hit;
	}
}


void AIMovement::TransitionTo(EnemyState* state) {
	if (state && state != m_pState) {
		delete m_pState;
		m_pState = state;
		m_pState->OnEnter();
	}
}

void AIMovement::EnableMovement(bool enable) {

	if (enable) {
		TransitionTo(new Turning(this));
	}

	m_CanMove = enable;
}