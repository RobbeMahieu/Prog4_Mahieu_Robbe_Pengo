#pragma once
#include "glm/glm.hpp"
#include "GameObject.h"
#include "Keyboard.h"
#include "XBoxController.h"

namespace pengo {

	engine::GameObject* CreatePlayer(std::string spritePath, engine::Keyboard* keyboard, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
	engine::GameObject* CreatePlayer(std::string spritePath, engine::XBoxController* keyboard, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
	engine::GameObject* CreatePlayerHUD(engine::GameObject* player, glm::vec3 position = glm::vec3{ 0,0,0 });
}