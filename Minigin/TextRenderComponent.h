#pragma once
#include <string>
#include "Font.h"
#include "Texture2D.h"
#include <memory>
#include "Component.h"

namespace engine {

	class TextRenderComponent : public Component
	{
	public:
		TextRenderComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextRenderComponent() = default;

		TextRenderComponent(const TextRenderComponent& other) = delete;
		TextRenderComponent(TextRenderComponent&& other) = delete;
		TextRenderComponent& operator=(const TextRenderComponent& other) = delete;
		TextRenderComponent& operator=(TextRenderComponent&& other) = delete;

		virtual void Update(float /*elapsedSec*/) {};
		virtual void FixedUpdate(float /*elapsedSec*/) {};
		virtual void Render() const override;
		void SetText(const std::string& text);

	private:
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

		void UpdateTexture();
	};
}

