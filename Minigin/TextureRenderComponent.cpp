#include "TextureRenderComponent.h"
#include <stdexcept>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

TextureRenderComponent::TextureRenderComponent(dae::GameObject* pOwner, const std::string& filePath) 
	: Component(pOwner)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
}

void TextureRenderComponent::Render() const {

	if (m_Texture) {
		const glm::vec3 position{ m_pOwner->GetWorldPosition() };
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, position.x, position.y);
	}
}