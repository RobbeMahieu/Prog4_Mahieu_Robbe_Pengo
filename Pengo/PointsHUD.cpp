#include "PointsHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "PointComponent.h"

using namespace std::placeholders;

PointsHUD::PointsHUD(dae::GameObject* pOwner, PointComponent* pPointComponent)
	: Component(pOwner)
	, m_pTextRenderer{ pOwner->GetComponent<TextRenderComponent>() }
{
	pPointComponent->ScoreChanged.AddObserver(this);
	OnNotify(pPointComponent->GetScore());
}

void PointsHUD::OnNotify(int score) {
	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Points: " + std::to_string(score));
	}
}
