#pragma once
#include <Component.h>
#include <GameObject.h>
#include <vector>
#include <string>

namespace pengo {

	class LevelLoader : public engine::Component
	{
		public:
			LevelLoader(engine::GameObject* pOwner, float gridSize);
			virtual ~LevelLoader() = default;

			LevelLoader(const LevelLoader& other) = delete;
			LevelLoader(LevelLoader&& other) = delete;
			LevelLoader& operator=(const LevelLoader& other) = delete;
			LevelLoader& operator=(LevelLoader&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {}

			void AddLevelPath(const std::string& path);
			engine::GameObject* LoadLevel(int index) const;

		private:
			std::vector<std::string> m_LevelPaths;
			float m_GridSize;

	};

}

