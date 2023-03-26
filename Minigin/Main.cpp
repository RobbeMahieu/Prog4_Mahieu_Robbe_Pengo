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
#include "BasicMovement.h"
#include "FPSComponent.h"
#include "XBoxController.h"
#include "Keyboard.h"

void load()
{
	// Add input devices
	// (I'd like to do this automatically in the future)
	InputDevice* controller0 = dae::InputManager::GetInstance().AddInputDevice<XBoxController>(0);
	InputDevice* keyboard = dae::InputManager::GetInstance().AddInputDevice<Keyboard>();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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

	float movementSpeed{ 100.0f };

	// Character
	auto character = new dae::GameObject();
	character->SetLocalPosition(0, 0);
	character->AddComponent<TextureRenderComponent>("../Data/pengo.png");
	character->AddComponent<BasicMovement>(movementSpeed, keyboard);
	scene.Add(character);

	// Enemy
	auto enemy = new dae::GameObject();
	enemy->SetLocalPosition(0, 0);
	enemy->AddComponent<TextureRenderComponent>("../Data/snowbee.png");
	enemy->AddComponent<BasicMovement>(movementSpeed*2, controller0);
	scene.Add(enemy);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}