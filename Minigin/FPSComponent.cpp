#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"

FPSComponent::FPSComponent(std::string textRenderName) 
	: dae::Component()
	, m_TextRenderName{ textRenderName }
{
}

void FPSComponent::Update(float elapsedSec) {
	m_Fps = 1.0f / elapsedSec;

	TextRenderComponent* textRenderer = dynamic_cast<TextRenderComponent*>(m_pGameObject->GetComponent(m_TextRenderName));
	if (textRenderer) {
		textRenderer->SetText(std::to_string(int(m_Fps)) + " FPS");
	}
}