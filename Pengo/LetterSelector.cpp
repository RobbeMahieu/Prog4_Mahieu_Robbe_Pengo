#include "LetterSelector.h"
#include <InputManager.h>
#include "FunctionCommand.h"

using namespace pengo;


LetterSelector::LetterSelector(engine::GameObject* pOwner, engine::Keyboard* device)
	: LetterSelector(pOwner)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, m_pLetterUp.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, m_pLetterDown.get(), device->GetID(), engine::KeyState::OnPress);
}

LetterSelector::LetterSelector(engine::GameObject* pOwner, engine::XBoxController* device)
	: LetterSelector(pOwner)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_UP, m_pLetterUp.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_DOWN, m_pLetterDown.get(), device->GetID(), engine::KeyState::OnPress);

}

LetterSelector::LetterSelector(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_Letter{ 'A' }
	, m_IsEnabled{ true }
	, m_pLetterUp{ std::make_unique<FunctionCommand>(std::bind(&LetterSelector::ChangeLetter, this, 1)) }
	, m_pLetterDown{ std::make_unique<FunctionCommand>(std::bind(&LetterSelector::ChangeLetter, this, -1)) }
	, m_TextRenderer{ m_pOwner->GetComponent<engine::TextRenderComponent>() }

{
}

LetterSelector::~LetterSelector() {
	engine::InputManager::GetInstance().UnbindAction(m_pLetterUp.get());
	engine::InputManager::GetInstance().UnbindAction(m_pLetterDown.get());
}

void LetterSelector::ChangeLetter(int amount) {
	if (!m_IsEnabled) { return; }
	
	m_Letter = char( int(m_Letter) + amount);

	if (int(m_Letter) < int('A')) {
		m_Letter = 'Z';
	}

	if (int(m_Letter) > int('Z')) {
		m_Letter = 'A';
	}

	const std::string text{ m_Letter };
	m_TextRenderer->SetText(text);
}

void LetterSelector::Enable(bool enable) {
	m_IsEnabled = enable;
}

char LetterSelector::GetLetter() const {
	return m_Letter;
}