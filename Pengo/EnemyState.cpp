#include "EnemyState.h"
#include "AIMovement.h"
#include "MoveCommand.h"

using namespace pengo;

// -- Base State --

EnemyState::EnemyState(AIMovement* pMovement)
	: m_pMovement{ pMovement }
{

}

// -- Moving State --

Moving::Moving(AIMovement* pMovement)
	: EnemyState(pMovement)
	, m_DirectionCount{ 0 }
{
}

void Moving::OnEnter() {
	m_pMovement->UpdateOptions();
	m_DirectionCount = int(std::count_if(m_pMovement->m_MovementOptions.begin(), m_pMovement->m_MovementOptions.end(), [](auto& element) { return !element.first; }));
}

EnemyState* Moving::Update() {

	m_pMovement->m_CurrentOption->Execute();

	// Check if extra option happened
	m_pMovement->UpdateOptions();
	int newCount = int(std::count_if(m_pMovement->m_MovementOptions.begin(), m_pMovement->m_MovementOptions.end(), [](auto& element) { return !element.first; }));

	if (newCount > m_DirectionCount) {
		return new Turning(m_pMovement);
	}

	m_DirectionCount = newCount;
	return nullptr;

}

EnemyState* Moving::HandleCollision(CollisionComponent* other) {
	
	if (other->GetLayer() == CollisionLayer::DYNAMIC) {
		return new Stuck(m_pMovement);
	}
	
	if (other->GetLayer() == CollisionLayer::PLAYER || other->GetLayer() == CollisionLayer::ENEMY) { return nullptr; }

	return new Turning(m_pMovement);
}

// -- Turning State --
Turning::Turning(AIMovement* pMovement)
	: EnemyState(pMovement)
{
}

EnemyState* Turning::Update() {

	// Get Latest options
	m_pMovement->UpdateOptions();

	// Get all valid commands
	std::vector<MoveCommand*> validOptions{};
	std::transform(m_pMovement->m_MovementOptions.begin(), m_pMovement->m_MovementOptions.end(), std::inserter(validOptions, validOptions.begin()), [](DirectionOption& option) {
		return (option.first) ? nullptr : option.second.get();
		});
	validOptions.erase(std::remove_if(validOptions.begin(), validOptions.end(), [](MoveCommand* option) { return !option; }), validOptions.end());

	// No valid moves, should stop
	if (validOptions.size() == 0) {
		m_pMovement->m_CurrentOption = m_pMovement->m_FallbackOption.get();
		return nullptr;
	}

	// Remove backtracking option
	if (validOptions.size() > 1) {

		validOptions.erase(std::remove_if(validOptions.begin(), validOptions.end(), [&](MoveCommand* option) {

			return  m_pMovement->m_CurrentOption->GetDirection() == (option->GetDirection() * glm::vec2{ -1,-1 });

		}), validOptions.end());
	}

	std::shuffle(validOptions.begin(), validOptions.end(), m_pMovement->m_RandomEngine);
	m_pMovement->m_CurrentOption = validOptions[0];

	return new Moving(m_pMovement);
}

EnemyState* Turning::HandleCollision(CollisionComponent* other) {
	if (other->GetLayer() == CollisionLayer::DYNAMIC) { 
		return new Stuck(m_pMovement); 
	}

	return nullptr;
}

// -- Stuck State --
Stuck::Stuck(AIMovement* pMovement)
	: EnemyState(pMovement)
{
}

EnemyState* Stuck::HandleCollision(CollisionComponent* other) {
	if (other->GetLayer() == CollisionLayer::STATIC) { 
		return new Die(m_pMovement); 
	}

	return nullptr;
}

// -- Die State -- 
Die::Die(AIMovement* pMovement)
	: EnemyState(pMovement)
{
	m_pMovement->GetOwner()->Destroy();
}