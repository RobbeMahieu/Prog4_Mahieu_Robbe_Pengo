#include "TextRenderComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "GameObject.h"

using namespace engine;

TextRenderComponent::TextRenderComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font)
	: Component(pOwner)
	, m_Text{ "" }
	, m_Font{ std::move(font) }
	, m_TextTexture{ nullptr }
{
	SetText(text);
}

void TextRenderComponent::Render() const{
	
	if (m_TextTexture)
	{
		const glm::vec3 position{ m_pOwner->GetWorldPosition() };
		Renderer::GetInstance().RenderTexture(*m_TextTexture, position.x, position.y);
	}
}

void TextRenderComponent::SetText(const std::string& text) {
	m_Text = text;
	UpdateTexture();
}

void TextRenderComponent::UpdateTexture() {

	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextTexture = std::make_shared<Texture2D>(texture);
}