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
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::unique_ptr<dae::Component> textRendererComp = std::make_unique<TextRenderComponent>("test", font);
	go->AddComponent("TextRenderer", std::move(textRendererComp));
	std::unique_ptr<dae::Component> FPSComp = std::make_unique<FPSComponent>("TextRenderer");
	go->AddComponent("FPSComponent", std::move(FPSComp));
	go->SetPosition(0, 0);
	scene.Add(go);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}