#include "PointsHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "PointManager.h"

using namespace pengo;

PointsHUD::PointsHUD(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_pTextRenderer{ pOwner->GetComponent<engine::TextRenderComponent>() }
{
	PointManager::GetInstance().ScoreChanged.AddObserver(this);
	OnNotify(PointManager::GetInstance().GetScore());
}

void PointsHUD::OnNotify(int /*score*/ ) {
	if (m_pTextRenderer) {

		m_pTextRenderer->SetText(PointManager::GetInstance().GetScoreText());
	}
}
