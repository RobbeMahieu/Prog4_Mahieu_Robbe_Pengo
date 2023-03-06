#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "CircleRotationComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Background
	auto background = std::make_shared<dae::GameObject>();
	background->SetLocalPosition(0, 0);
	auto bgTextureRenderer = std::make_unique<TextureRenderComponent>("../Data/background.tga");
	background->AddComponent("Texture", std::move(bgTextureRenderer));
	scene.Add(background);

	// FPS counter
	auto FPSCounter = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::unique_ptr<dae::Component> textRendererComp = std::make_unique<TextRenderComponent>("test", font);
	FPSCounter->AddComponent("TextRenderer", std::move(textRendererComp));
	std::unique_ptr<dae::Component> FPSComp = std::make_unique<FPSComponent>("TextRenderer");
	FPSCounter->AddComponent("FPSComponent", std::move(FPSComp));
	FPSCounter->SetLocalPosition(0, 0);
	scene.Add(FPSCounter);

	// Rotate Point
	auto rotatePoint = std::make_shared<dae::GameObject>();
	rotatePoint->SetLocalPosition(300, 250);
	scene.Add(rotatePoint);

	// Character
	auto character = std::make_shared<dae::GameObject>();
	character->SetLocalPosition(0, 0);
	auto characterTextureRenderer = std::make_unique<TextureRenderComponent>("../Data/pengo.png");
	auto characterRotator = std::make_unique<CircleRotationComponent>(2.0f, 100.0f);
	character->AddComponent("Texture", std::move(characterTextureRenderer));
	character->AddComponent("Rotator", std::move(characterRotator));
	character->SetParent(rotatePoint, false);
	scene.Add(character);

	// Enemy
	auto enemy = std::make_shared<dae::GameObject>();
	enemy->SetLocalPosition(0, 0);
	auto enemyTextureRenderer = std::make_unique<TextureRenderComponent>("../Data/snowbee.png");
	enemy->AddComponent("Texture", std::move(enemyTextureRenderer));
	auto enemyRotator = std::make_unique<CircleRotationComponent>(-5.0f, 40.0f);
	enemy->AddComponent("Rotator", std::move(enemyRotator));
	enemy->SetParent(character, false);
	scene.Add(enemy);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}