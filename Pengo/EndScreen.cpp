#include "EndScreen.h"
#include <iostream>
#include <TextureRenderComponent.h>
#include <TextRenderComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include "MenuInteractor.h"
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

	// Buttons
	auto buttonFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 25);

	engine::GameObject* button = new engine::GameObject();
	button->SetLocalPosition(120, 380);
	button->AddComponent<engine::TextRenderComponent>("PLAY AGAIN", buttonFont);
	button->AttachTo(m_pScreen, true);
	m_pButtons.push_back(button);

	button = new engine::GameObject();
	button->SetLocalPosition(120, 430);
	button->AddComponent<engine::TextRenderComponent>("MENU", buttonFont);
	button->AttachTo(m_pScreen, true);
	m_pButtons.push_back(button);

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
	m_pCursor->SetLocalPosition(-45, -5);
	m_pCursor->AddComponent<engine::TextureRenderComponent>("Sprites/cursor.png");
	m_pCursor->AttachTo(m_pButtons[0], false);

	// Input
	std::vector<engine::InputDevice*> devices{ engine::InputManager::GetInstance().GetInputDevices() };
	for (engine::InputDevice* device : devices) {

		engine::Keyboard* keyboard{ dynamic_cast<engine::Keyboard*>(device) };
		if (keyboard) {
			m_pScreen->AddComponent<MenuInteractor>(int(m_pButtons.size()), keyboard);
			continue;
		}

		engine::XBoxController* controller{ dynamic_cast<engine::XBoxController*>(device) };
		if (controller) {
			m_pScreen->AddComponent<MenuInteractor>(int(m_pButtons.size()), controller);
			continue;
		}
	}
}

GameState* EndScreen::Update() {

	// Get selected index
	int index{ MenuInteractor::GetSelectedIndex() };

	// Updated selected item
	if (m_pCursor->GetParent() != m_pButtons[index]) {
		m_pCursor->AttachTo(m_pButtons[index], false);
	}

	if (MenuInteractor::GetOptionChosen()) {

		if (index == 0) {
			return new Playing(m_pOwner, m_GameMode);
		}
		else {
			return new Menu(m_pOwner);
		}
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

	// Add current score to the score list
	m_HighScores.push_back(PointManager::GetInstance().GetScoreText());

	// Sort high scores
	std::sort(m_HighScores.begin(), m_HighScores.end(), [](const std::string& a, const std::string& b) {
		int numA{ std::stoi(a) };
		int numB{ std::stoi(b) };
		return numA > numB;
	});

	if (std::ofstream output{ "../Data/scores.txt" }; output.is_open()) {

		for (int i{ 0 }; i < std::min(HighscoreAmount, int(m_HighScores.size())); ++i) {
			output << m_HighScores[i] << "\n";
		}
	}
}