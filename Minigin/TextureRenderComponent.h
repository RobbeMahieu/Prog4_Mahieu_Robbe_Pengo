#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <memory>
#include <string>

namespace engine {

	class TextureRenderComponent : public Component
	{
	public:
		TextureRenderComponent(GameObject* pOwner, const std::string& texturePath);
		virtual ~TextureRenderComponent() = default;

		TextureRenderComponent(const TextureRenderComponent& other) = delete;
		TextureRenderComponent(TextureRenderComponent&& other) = delete;
		TextureRenderComponent& operator=(const TextureRenderComponent& other) = delete;
		TextureRenderComponent& operator=(TextureRenderComponent&& other) = delete;

		virtual void Render() const override;
		virtual void Update(float /*elapsedSec*/) {};
		virtual void FixedUpdate(float /*elapsedSec*/) {};

	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}

