#include "Block.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "SlidingComponent.h"

using namespace pengo;

engine::GameObject* pengo::CreateBlock(std::string texturePath, glm::vec3 position, float size, PhysicsType type) {
	engine::GameObject* block = new engine::GameObject();
	block->AddComponent<engine::TextureRenderComponent>(texturePath);
	block->AddComponent<CollisionComponent>(size, size, false, type);

	block->SetLocalPosition(position);

	return block;
}

engine::GameObject* pengo::CreateWallBlock(glm::vec3 position) {
	return CreateBlock("wall.png", position, 16, PhysicsType::STATIC);
}

engine::GameObject* pengo::CreateIceBlock(glm::vec3 position) {
	engine::GameObject* block = CreateBlock("ice.png", position, 32, PhysicsType::STATIC);
	block->AddComponent<SlidingComponent>(40.0f);
	return block;
}