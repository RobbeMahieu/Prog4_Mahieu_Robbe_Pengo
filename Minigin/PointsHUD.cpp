#include "PointsHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "EventManager.h"
#include "PointComponent.h"

using namespace std::placeholders;

PointsHUD::PointsHUD(dae::GameObject* pOwner, PointComponent* pPointComponent)
	: Component(pOwner)
	, m_ScoreIncreaseListener{ std::make_unique<Observer>(std::bind(&PointsHUD::OnPointIncrease, this, _1)) }
	, m_pPointComponent{ pPointComponent }
	, m_pTextRenderer{ pOwner->GetComponent<TextRenderComponent>() }
{
	EventManager::GetInstance().AddListener(EventType::ScoreIncrease, m_ScoreIncreaseListener.get());

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Points: " + std::to_string(m_pPointComponent->GetScore()));
	}
}

void PointsHUD::OnPointIncrease(dae::GameObject* damagedObject) {

	if (damagedObject->GetComponent<PointComponent>() != m_pPointComponent) {
		return;
	}

	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Points: " + std::to_string(m_pPointComponent->GetScore()));
	}
}
