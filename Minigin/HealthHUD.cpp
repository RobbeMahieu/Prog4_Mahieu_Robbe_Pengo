#include "HealthHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "EventManager.h"
#include "HealthComponent.h"
using namespace std::placeholders;

HealthHUD::HealthHUD(dae::GameObject* pOwner, HealthComponent* pHealthComponent)
	: Component(pOwner)
	, m_pDeathListener{ std::make_unique<Observer>(std::bind(&HealthHUD::OnDeath, this, _1)) }
	, m_pGameOverListener{ std::make_unique<Observer>(std::bind(&HealthHUD::OnGameOver, this, _1)) }
	, m_pHealthComponent{ pHealthComponent }
	, m_pTextRenderer{ pOwner->GetComponent<TextRenderComponent>() }
{
	EventManager::GetInstance().AddListener(EventType::PlayerDied, m_pDeathListener.get());
	EventManager::GetInstance().AddListener(EventType::GameOver, m_pGameOverListener.get());

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Lives: " + std::to_string(m_pHealthComponent->GetHealth()));
	}
}

void HealthHUD::OnDeath(dae::GameObject* damagedObject) {

	if (damagedObject->GetComponent<HealthComponent>() != m_pHealthComponent) {
		return;
	}

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Lives: " + std::to_string(m_pHealthComponent->GetHealth()));
	}
}

void HealthHUD::OnGameOver(dae::GameObject* damagedObject) {

	if (damagedObject->GetComponent<HealthComponent>() != m_pHealthComponent) {
		return;
	}

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Game Over!");
	}
}