#include "PointsHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "PointManager.h"
#include <sstream>
#include <iomanip>

using namespace pengo;

PointsHUD::PointsHUD(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_pTextRenderer{ pOwner->GetComponent<engine::TextRenderComponent>() }
{
	PointManager::GetInstance().ScoreChanged.AddObserver(this);
	OnNotify(PointManager::GetInstance().GetScore());
}

void PointsHUD::OnNotify(int score) {
	if (m_pTextRenderer) {

		std::stringstream ss;
		ss << std::setw(8) << std::setfill('0') << score;
		m_pTextRenderer->SetText(ss.str());
	}
}
