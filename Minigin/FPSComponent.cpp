#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"

FPSComponent::FPSComponent(dae::GameObject* pOwner) 
	: Component(pOwner)
	, m_Fps{ 0.0f }
{
}

void FPSComponent::Update(float elapsedSec) {
	m_Fps = 1.0f / elapsedSec;

	TextRenderComponent* textRenderer = m_pOwner->GetComponent<TextRenderComponent>();
	if (textRenderer) {
		textRenderer->SetText(std::to_string(int(m_Fps)) + " FPS");
	}
}