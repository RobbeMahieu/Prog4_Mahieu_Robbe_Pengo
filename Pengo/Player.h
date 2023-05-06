#pragma once
#include "Minigin.h"
#include "glm/glm.hpp"

namespace dae {
	class GameObject;
}

class Keyboard;
class XBoxController;

dae::GameObject* CreatePlayer(std::string spritePath, Keyboard* keyboard, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
dae::GameObject* CreatePlayer(std::string spritePath, XBoxController* keyboard, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
dae::GameObject* CreatePlayerHUD(dae::GameObject* player, glm::vec3 position = glm::vec3{ 0,0,0 });