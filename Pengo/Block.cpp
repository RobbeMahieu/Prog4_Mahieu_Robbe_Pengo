#include "Block.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "CollisionComponent.h"
#include "SlidingComponent.h"

dae::GameObject* CreateBlock(std::string texturePath, glm::vec3 position, int size, PhysicsType type) {
	dae::GameObject* block = new dae::GameObject();
	block->AddComponent<TextureRenderComponent>(texturePath);
	block->AddComponent<CollisionComponent>(size, size, false, type);

	block->SetLocalPosition(position);

	return block;
}

dae::GameObject* CreateWallBlock(glm::vec3 position) {
	return CreateBlock("wall.png", position, 16, PhysicsType::STATIC);
}

dae::GameObject* CreateIceBlock(glm::vec3 position) {
	dae::GameObject* block = CreateBlock("ice.png", position, 32, PhysicsType::MOVABLE);
	block->AddComponent<SlidingComponent>(40.0f);
	return block;
}