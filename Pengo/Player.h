#pragma once
#include "glm/glm.hpp"
#include "GameObject.h"
#include "Keyboard.h"
#include "XBoxController.h"

namespace pengo {

	engine::GameObject* CreatePlayer(std::string spritePath, engine::Keyboard* keyboard, engine::XBoxController* controller, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
	engine::GameObject* CreateControllableSnowBee(std::string spritePath, engine::Keyboard* keyboard, engine::XBoxController* controller, glm::vec3 position = glm::vec3{ 0,0,0 });
	engine::GameObject* CreatePlayerHUD(engine::GameObject* player, std::string iconPath, int index, glm::vec3 position = glm::vec3{ 0,0,0 });
}