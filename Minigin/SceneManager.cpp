#include "SceneManager.h"
#include "Scene.h"

using namespace engine;

void SceneManager::Update(float elapsedSec)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(elapsedSec);
	}
}

void SceneManager::FixedUpdate(float elapsedSec)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(elapsedSec);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
