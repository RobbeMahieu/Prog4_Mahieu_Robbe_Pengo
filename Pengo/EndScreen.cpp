#include "EndScreen.h"
#include <iostream>
#include <TextureRenderComponent.h>
#include <TextRenderComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include "MenuHorizontalInteractor.h"
#include "LetterSelector.h"
#include "Playing.h"
#include "Menu.h"
#include "PointManager.h"
#include <fstream>

using namespace pengo;

EndScreen::EndScreen(engine::GameObject* pOwner, bool didWin, GameMode mode)
	: GameState(pOwner)
	, m_DidWin{ didWin }
	, m_pScreen{ nullptr }
	, m_pCursor{ nullptr }
	, m_GameMode{ mode }
{
}

void EndScreen::OnLeave() {
	m_pScreen->Destroy();
	SaveHighscores();
}

void EndScreen::OnEnter() {


	// Create menu
	m_pScreen = new engine::GameObject();
	m_pScreen->AttachTo(m_pOwner, false);

	// Add title
	auto titleFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 40);
	auto textFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 15);

	std::string titleText{ m_DidWin ? "YOU WON!" : "GAME OVER" };
	engine::GameObject* title = new engine::GameObject();
	title->SetLocalPosition(50, 50);
	title->AddComponent<engine::TextRenderComponent>(titleText, titleFont);
	title->AttachTo(m_pScreen, true);

	std::string scoreText{ "SCORE: " + PointManager::GetInstance().GetScoreText() };
	engine::GameObject* score = new engine::GameObject();
	score->SetLocalPosition(110, 110);
	score->AddComponent<engine::TextRenderComponent>(scoreText, textFont);
	score->AttachTo(m_pScreen, true);

	// Letter Selectors
	auto buttonFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 25);

	engine::GameObject* button = new engine::GameObject();
	button->AddComponent<engine::TextRenderComponent>("A", buttonFont);
	button->SetLocalPosition(170, 350);
	button->AttachTo(m_pScreen, false);
	m_pLetterSelectors.push_back(button);

	button = new engine::GameObject();
	button->AddComponent<engine::TextRenderComponent>("A", buttonFont);
	button->SetLocalPosition(200, 350);
	button->AttachTo(m_pScreen, false);
	m_pLetterSelectors.push_back(button);

	button = new engine::GameObject();
	button->AddComponent<engine::TextRenderComponent>("A", buttonFont);
	button->SetLocalPosition(230, 350);
	button->AttachTo(m_pScreen, false);
	m_pLetterSelectors.push_back(button);

	// Add Scores
	LoadHighscores();
	std::string highscoreText{ "---- HIGH SCORES ---- " };
	engine::GameObject* highScores = new engine::GameObject();
	highScores->SetLocalPosition(70, 160);
	highScores->AddComponent<engine::TextRenderComponent>(highscoreText, textFont);
	highScores->AttachTo(m_pScreen, true);

	for (int i{ 0 }; i < m_HighScores.size(); ++i) {
		engine::GameObject* highscore = new engine::GameObject();
		highscore->SetLocalPosition(60, 5 + 20.0f * (1 + i));
		highscore->AddComponent<engine::TextRenderComponent>(m_HighScores[i], textFont);
		highscore->AttachTo(highScores, false);
	}

	// Cursor
	m_pCursor = new engine::GameObject();
	m_pCursor->SetLocalPosition(0, -25);
	m_pCursor->AddComponent<engine::TextureRenderComponent>("Sprites/cursor2.png");
	m_pCursor->AttachTo(m_pLetterSelectors[0], false);

	// Input
	std::vector<engine::InputDevice*> devices{ engine::InputManager::GetInstance().GetInputDevices() };
	for (engine::InputDevice* device : devices) {

		engine::Keyboard* keyboard{ dynamic_cast<engine::Keyboard*>(device) };
		if (keyboard) {
			m_pScreen->AddComponent<MenuHorizontalInteractor>(int(m_pLetterSelectors.size()), keyboard);

			for (engine::GameObject* selector : m_pLetterSelectors) {
				selector->AddComponent<LetterSelector>(keyboard);
			}

			continue;
		}

		engine::XBoxController* controller{ dynamic_cast<engine::XBoxController*>(device) };
		if (controller) {
			m_pScreen->AddComponent<MenuHorizontalInteractor>(int(m_pLetterSelectors.size()), controller);

			for (engine::GameObject* selector : m_pLetterSelectors) {
				selector->AddComponent<LetterSelector>(controller);
			}
			continue;
		}
	}
}

GameState* EndScreen::Update() {

	// Get selected index
	int index{ MenuHorizontalInteractor::GetSelectedIndex() };

	// Enable right selector
	for (int i{ 0 }; i < m_pLetterSelectors.size(); ++i) {
		bool active{ i == index };
		m_pLetterSelectors[i]->GetComponent<LetterSelector>()->Enable(active);
	}

	// Updated selected item
	if (m_pCursor->GetParent() != m_pLetterSelectors[index]) {
		m_pCursor->AttachTo(m_pLetterSelectors[index], false);
	}

	// Go back to menu by submitting
	if (MenuHorizontalInteractor::GetOptionChosen()) {

		return new Menu(m_pOwner);
	}

	return nullptr;
}

void EndScreen::LoadHighscores() {
	if (std::ifstream input{ "../Data/scores.txt" }; input.is_open()) {

		std::string line{};

		while (!input.eof()) {
			std::getline(input, line);
			if (!line.empty()) {
				m_HighScores.push_back(line);
			}
		}
	}
}

void EndScreen::SaveHighscores() {

	int HighscoreAmount{ 5 };

	// Create score
	std::string score{};

	for (engine::GameObject* selector : m_pLetterSelectors) {
		score += selector->GetComponent<LetterSelector>()->GetLetter();
	}

	score += " " + PointManager::GetInstance().GetScoreText();

	// Add current score to the score list
	m_HighScores.push_back(score);

	// Sort high scores
	std::sort(m_HighScores.begin(), m_HighScores.end(), [](const std::string& a, const std::string& b) {
		
		int numA{ std::stoi(a.substr(3,8)) };
		int numB{ std::stoi(b.substr(3,8)) };
		return numA > numB;
	});

	if (std::ofstream output{ "../Data/scores.txt" }; output.is_open()) {

		for (int i{ 0 }; i < std::min(HighscoreAmount, int(m_HighScores.size())); ++i) {
			output << m_HighScores[i] << "\n";
		}
	}
}