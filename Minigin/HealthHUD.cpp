#include "HealthHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "EventManager.h"
#include "HealthComponent.h"

HealthHUD::HealthHUD(dae::GameObject* pOwner, HealthComponent* pHealthComponent)
	: Component(pOwner)
	, m_pHealthComponent{ pHealthComponent }
	, m_pTextRenderer{ pOwner->GetComponent<TextRenderComponent>() }
{
	EventManager::GetInstance().AddListener(EventType::PlayerDamage, this);
	EventManager::GetInstance().AddListener(EventType::GameOver, this);

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Lives: " + std::to_string(m_pHealthComponent->GetHealth()));
	}
}

void HealthHUD::OnNotify(EventType event, dae::GameObject* damagedObject) {

	if (damagedObject->GetComponent<HealthComponent>() != m_pHealthComponent) {
		return;
	}

	switch (event) {

		case EventType::PlayerDamage:
			if (m_pTextRenderer) {
				m_pTextRenderer->SetText("Lives: " + std::to_string(m_pHealthComponent->GetHealth()));
			}
			break;

		case EventType::GameOver:
			if (m_pTextRenderer) {
				m_pTextRenderer->SetText("Game Over!");
			}
			break;
	}
}