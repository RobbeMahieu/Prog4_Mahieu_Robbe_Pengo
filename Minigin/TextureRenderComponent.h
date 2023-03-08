#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <memory>
#include <string>

class TextureRenderComponent : public Component
{
public:
	TextureRenderComponent(dae::GameObject* pOwner, const std::string& texturePath);
	virtual ~TextureRenderComponent() = default;

	TextureRenderComponent(const TextureRenderComponent& other) = delete;
	TextureRenderComponent(TextureRenderComponent&& other) = delete;
	TextureRenderComponent& operator=(const TextureRenderComponent& other) = delete;
	TextureRenderComponent& operator=(TextureRenderComponent&& other) = delete;

	virtual void Render() const override;
	virtual void Update([[maybe_unused]] float elapsedSec) {};
	virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {};

private:
	std::shared_ptr<dae::Texture2D> m_Texture;
};

