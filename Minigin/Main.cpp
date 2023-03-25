#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "CircleRotationComponent.h"
#include "FPSComponent.h"
#include "XBoxController.h"
#include "Keyboard.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Add input devices
	dae::InputManager::GetInstance().AddInputDevice(new XBoxController(0));
	dae::InputManager::GetInstance().AddInputDevice(new Keyboard());

	// Add key bindings
	dae::InputManager::GetInstance().BindAction(0x1000, new Command([]() {std::cout << "It Works!\n"; }));
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, new Command([]() {std::cout << "It Works!\n"; }), 1);

	// Remove testing
	auto parent = new dae::GameObject();
	scene.Add(parent);

	auto object = new dae::GameObject();
	object->AddComponent<TextureRenderComponent>("../Data/background.tga");
	object->AddComponent<FPSComponent>();
	object->RemoveComponent<FPSComponent>();
	object->AttachTo(parent, true);

	auto object2 = new dae::GameObject();
	object2->AddComponent<TextureRenderComponent>("../Data/background.tga");
	object2->AttachTo(parent, true);
	scene.Add(object2);
	object2->AttachTo(nullptr, false); 			

	scene.Remove(parent);

	// Background
	auto background = new dae::GameObject();
	background->SetLocalPosition(0, 0);
	background->AddComponent<TextureRenderComponent>("../Data/background.tga");
	scene.Add(background);

	// FPS counter
	auto FPSCounter = new dae::GameObject();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPSCounter->AddComponent<TextRenderComponent>("test", font);
	FPSCounter->AddComponent<FPSComponent>();
	FPSCounter->SetLocalPosition(0, 0);
	scene.Add(FPSCounter);

	// Rotate Point
	auto rotatePoint = new dae::GameObject();
	rotatePoint->SetLocalPosition(300, 250);
	scene.Add(rotatePoint);

	// Character
	auto character = new dae::GameObject();
	character->SetLocalPosition(0, 0);
	character->AddComponent<TextureRenderComponent>("../Data/pengo.png");
	character->AddComponent<CircleRotationComponent>(2.0f, 100.0f);
	character->AttachTo(rotatePoint, false);

	// Enemy
	auto enemy = new dae::GameObject();
	enemy->SetLocalPosition(0, 0);
	enemy->AddComponent<TextureRenderComponent>("../Data/snowbee.png");
	enemy->AddComponent<CircleRotationComponent>(-5.0f, 40.0f);
	enemy->AttachTo(character, false);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}