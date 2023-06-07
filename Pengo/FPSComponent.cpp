#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "GameTime.h"

using namespace pengo;

FPSComponent::FPSComponent(engine::GameObject* pOwner) 
	: Component(pOwner)
	, m_Fps{ 0.0f }
{
}

void FPSComponent::Update() {
	m_Fps = 1.0f / engine::GameTime::GetInstance().GetElapsedSec();

	engine::TextRenderComponent* textRenderer = m_pOwner->GetComponent<engine::TextRenderComponent>();
	if (textRenderer) {
		textRenderer->SetText(std::to_string(int(m_Fps)) + " FPS");
	}
}