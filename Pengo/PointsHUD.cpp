#include "PointsHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "EventManager.h"
#include "PointComponent.h"

using namespace std::placeholders;

PointsHUD::PointsHUD(dae::GameObject* pOwner, PointComponent* pPointComponent)
	: Component(pOwner)
	, m_pPointComponent{ pPointComponent }
	, m_pTextRenderer{ pOwner->GetComponent<TextRenderComponent>() }
{
	EventManager::GetInstance().AddListener(EventType::ScoreIncrease, this);

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Points: " + std::to_string(m_pPointComponent->GetScore()));
	}
}

void PointsHUD::OnNotify(EventType event, dae::GameObject* damagedObject) {

	if (damagedObject->GetComponent<PointComponent>() != m_pPointComponent) {
		return;
	}

	if (event == EventType::ScoreIncrease) {
		if (m_pTextRenderer) {
			m_pTextRenderer->SetText("Points: " + std::to_string(m_pPointComponent->GetScore()));
		}
	}
}
