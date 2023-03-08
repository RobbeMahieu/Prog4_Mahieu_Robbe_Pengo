#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"

FPSComponent::FPSComponent(dae::GameObject* pOwner, std::string textRenderName) 
	: Component(pOwner)
	, m_TextRenderName{ textRenderName }
	, m_Fps{ 0.0f }
{
}

void FPSComponent::Update(float elapsedSec) {
	m_Fps = 1.0f / elapsedSec;

	TextRenderComponent* textRenderer = dynamic_cast<TextRenderComponent*>(m_pOwner->GetComponent(m_TextRenderName));
	if (textRenderer) {
		textRenderer->SetText(std::to_string(int(m_Fps)) + " FPS");
	}
}