#include "PointsHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "PointManager.h"

using namespace pengo;

PointsHUD::PointsHUD(engine::GameObject* pOwner, PointManager* pPointComponent)
	: Component(pOwner)
	, m_pTextRenderer{ pOwner->GetComponent<engine::TextRenderComponent>() }
{
	pPointComponent->ScoreChanged.AddObserver(this);
	OnNotify(pPointComponent->GetScore());
}

void PointsHUD::OnNotify(int score) {
	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Points: " + std::to_string(score));
	}
}
