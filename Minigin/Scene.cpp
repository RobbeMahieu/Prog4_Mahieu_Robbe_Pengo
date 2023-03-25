#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) 
	: m_name(name) 
	, m_SceneRoot{ new GameObject() }
{}

Scene::~Scene() {
	delete m_SceneRoot;
}

void Scene::Add(GameObject* object)
{
	object->AttachTo(m_SceneRoot, true);
}

void Scene::Remove(GameObject* object)
{
	object->AttachTo(nullptr, true);
}

void Scene::RemoveAll()
{
	delete m_SceneRoot;
	m_SceneRoot = new GameObject();
}

void Scene::Update(float elapsedSec)
{
	m_SceneRoot->Update(elapsedSec);
}

void Scene::FixedUpdate(float elapsedSec)
{
	m_SceneRoot->FixedUpdate(elapsedSec);
}

void Scene::Render() const
{
	m_SceneRoot->Render();
}