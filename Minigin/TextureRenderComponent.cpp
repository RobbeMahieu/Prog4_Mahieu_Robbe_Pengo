#include "TextureRenderComponent.h"
#include <stdexcept>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

TextureRenderComponent::TextureRenderComponent(const std::string& filePath) {
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
}

void TextureRenderComponent::Render() const {

	if (m_Texture) {
		const glm::vec3 position{ m_pGameObject->GetWorldPosition() };
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, position.x, position.y);
	}
}