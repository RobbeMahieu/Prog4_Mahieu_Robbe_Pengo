#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"

using namespace pengo;

FPSComponent::FPSComponent(engine::GameObject* pOwner) 
	: Component(pOwner)
	, m_Fps{ 0.0f }
{
}

void FPSComponent::Update(float elapsedSec) {
	m_Fps = 1.0f / elapsedSec;

	engine::TextRenderComponent* textRenderer = m_pOwner->GetComponent<engine::TextRenderComponent>();
	if (textRenderer) {
		textRenderer->SetText(std::to_string(int(m_Fps)) + " FPS");
	}
}