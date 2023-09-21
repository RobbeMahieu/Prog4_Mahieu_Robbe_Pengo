#pragma once
#include <Component.h>
#include <memory>
#include <Keyboard.h>
#include <XBoxController.h>
#include <TextRenderComponent.h>

namespace pengo {

	class FunctionCommand;

	class LetterSelector final : public engine::Component
	{
		public:

			LetterSelector(engine::GameObject* pOwner, engine::Keyboard* device);
			LetterSelector(engine::GameObject* pOwner, engine::XBoxController* device);
			virtual ~LetterSelector();

			LetterSelector(const LetterSelector& other) = delete;
			LetterSelector(LetterSelector&& other) = delete;
			LetterSelector& operator=(const LetterSelector& other) = delete;
			LetterSelector& operator=(LetterSelector&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}

			char GetLetter() const;

			void Enable(bool enable);

		private:
			bool m_IsEnabled;

			LetterSelector(engine::GameObject* pOwner);
			void ChangeLetter(int amount);

			char m_Letter;
			std::unique_ptr<FunctionCommand> m_pLetterUp;
			std::unique_ptr<FunctionCommand> m_pLetterDown;

			engine::TextRenderComponent* m_TextRenderer;
	};
}