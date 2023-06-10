#include "AIMovement.h"
#include "MoveCommand.h"
#include <GameTime.h>

using namespace pengo;

AIMovement::AIMovement(engine::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_MovementOptions{}
	, m_CurrentOption{ nullptr }
	, m_pCollider{ m_pOwner->GetComponent<CollisionComponent>() }
	, m_RandomEngine{ std::random_device{}() }
	, m_RandomNumber{0,10}
	, m_FallbackOption{ std::make_unique<MoveCommand>(pOwner, glm::vec2{ 0,0 }, speed) }
{
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ 0,-1 }, speed)));
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ 0,1 }, speed)));
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ 1,0 }, speed)));
	m_MovementOptions.emplace_back(std::make_pair(true, std::make_unique<MoveCommand>(pOwner, glm::vec2{ -1,0 }, speed)));

	m_CurrentOption = m_MovementOptions[0].second.get();

}

void AIMovement::Update() {

	UpdateOptions();
	ChooseDirection();


	if (m_CurrentOption) {
		m_CurrentOption->Execute();
	}
}

void AIMovement::ChooseDirection() {

	// Get all valid commands
	std::vector<MoveCommand*> validOptions{};
	std::transform(m_MovementOptions.begin(), m_MovementOptions.end(), std::inserter(validOptions, validOptions.begin()), [](DirectionOption& option) {
		return (option.first) ? nullptr : option.second.get();
	});
	validOptions.erase(std::remove_if(validOptions.begin(), validOptions.end(), [](MoveCommand* option) { return !option; }), validOptions.end());

	// No valid moves, should stop
	if (validOptions.size() == 0) {
		m_CurrentOption = m_FallbackOption.get();
		return;
	}

	// Remove backtracking option
	if (validOptions.size() > 1){

		validOptions.erase(std::remove_if(validOptions.begin(), validOptions.end(), [&](MoveCommand* option) { 
			
			return  m_CurrentOption->GetDirection() == (option->GetDirection() * glm::vec2{ -1,-1 });
			
		}), validOptions.end());
	}

	// Also, if the current direction is in there, add it a couple times more to increase the chance of going in the same direction
	if (std::find(validOptions.begin(), validOptions.end(), m_CurrentOption) != validOptions.end()) {
		int chanceIncrease{ 15 };
		for (int i{ 0 }; i < chanceIncrease; ++i) {
			validOptions.emplace_back(m_CurrentOption);
		}
	}

	std::shuffle(validOptions.begin(), validOptions.end(), m_RandomEngine);
	m_CurrentOption = validOptions[0];

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
		option.first = (hitResult.hit && hitResult.collider->GetType() != PhysicsType::DYNAMIC);

	}
}
