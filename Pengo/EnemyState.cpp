#include "EnemyState.h"
#include "AIMovement.h"
#include "MoveCommand.h"
#include "KillPlayerComponent.h"
#include "GameTime.h"
#include <GameServiceLocator.h>

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

	if (!m_pMovement->m_CanMove) { return nullptr; }

	m_pMovement->m_CurrentOption->Execute();

	// Check if extra option happened
	m_pMovement->UpdateOptions();
	const int newCount = int(std::count_if(m_pMovement->m_MovementOptions.begin(), m_pMovement->m_MovementOptions.end(), [](auto& element) { return !element.first; }));

	if (newCount > m_DirectionCount) {
		return new Turning(m_pMovement);
	}

	m_DirectionCount = newCount;
	return nullptr;

}

EnemyState* Moving::HandleCollision(CollisionComponent* other) {
	
	if (other->GetLayer() != CollisionLayer::STATIC ) { return nullptr; }

	return new Turning(m_pMovement);
}

// -- Turning State --
Turning::Turning(AIMovement* pMovement)
	: EnemyState(pMovement)
{
}

void Turning::OnEnter() {
	KillPlayerComponent* killComponent{ m_pMovement->m_pOwner->GetComponent<KillPlayerComponent>() };
	if (killComponent) {
		killComponent->Enable(true);
	}
}

EnemyState* Turning::Update() {

	if (!m_pMovement->m_CanMove) { return nullptr; }

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


