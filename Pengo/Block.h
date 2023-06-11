#pragma once
#include "Minigin.h"
#include "glm/glm.hpp"
#include "GameObject.h"
#include "CollisionComponent.h"

namespace pengo {
	engine::GameObject* CreateBlock(std::string texturePath, glm::vec3 position, float size, CollisionLayer layer);
	engine::GameObject* CreateIceBlock(glm::vec3 position);
	engine::GameObject* CreateWalls(float blockSize, float width, float height);

}
