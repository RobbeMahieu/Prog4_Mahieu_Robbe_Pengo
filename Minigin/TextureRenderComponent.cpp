#include "TextureRenderComponent.h"
#include <stdexcept>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

using namespace engine;

TextureRenderComponent::TextureRenderComponent(GameObject* pOwner, const std::string& filePath) 
	: Component(pOwner)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filePath);
}

void TextureRenderComponent::Render() const {

	if (m_Texture) {
		const glm::vec3 position{ m_pOwner->GetWorldPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture, position.x, position.y);
	}
}