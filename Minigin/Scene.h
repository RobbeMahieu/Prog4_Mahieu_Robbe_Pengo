#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace engine
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		GameObject* m_SceneRoot;

		static unsigned int m_idCounter; 
	};

}
