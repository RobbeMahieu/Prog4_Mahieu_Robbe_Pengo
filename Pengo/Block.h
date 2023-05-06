#pragma once
#include "Minigin.h"
#include "glm/glm.hpp"

namespace dae {
	class GameObject;
}

dae::GameObject* CreateBlock(std::string texturePath, glm::vec3 position, int size);
dae::GameObject* CreateIceBlock(glm::vec3 position);
dae::GameObject* CreateWallBlock(glm::vec3 position);
