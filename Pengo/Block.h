#pragma once
#include "Minigin.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include "CollisionComponent.h"

namespace pengo {
	engine::GameObject* CreateBlock(std::string texturePath, glm::vec3 position, int size, PhysicsType type);
	engine::GameObject* CreateIceBlock(glm::vec3 position);
	engine::GameObject* CreateWallBlock(glm::vec3 position);

}
