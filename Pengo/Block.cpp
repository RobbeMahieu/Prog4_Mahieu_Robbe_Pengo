#include "Block.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "SlidingComponent.h"
#include "StunComponent.h"

using namespace pengo;

engine::GameObject* pengo::CreateBlock(std::string texturePath, glm::vec3 position, float size, CollisionLayer layer) {
	engine::GameObject* block = new engine::GameObject();
	block->AddComponent<engine::TextureRenderComponent>(texturePath);
	block->AddComponent<CollisionComponent>(size, size, false, layer);

	block->SetLocalPosition(position);

	return block;
}

engine::GameObject* pengo::CreateWalls(float blockSize, float width, float height) {
	engine::GameObject* walls = new engine::GameObject();
	walls->AddComponent<engine::TextureRenderComponent>("Backgrounds/wall.png");

	engine::GameObject* topWall = new engine::GameObject();
	topWall->AddComponent<CollisionComponent>(width, blockSize, false, CollisionLayer::STATIC);
	topWall->AddComponent<StunComponent>();
	topWall->AttachTo(walls, false);

	engine::GameObject* bottomWall = new engine::GameObject();
	bottomWall->SetLocalPosition(0, height - blockSize);
	bottomWall->AddComponent<CollisionComponent>(width, blockSize, false, CollisionLayer::STATIC);
	bottomWall->AddComponent<StunComponent>();
	bottomWall->AttachTo(walls, false);

	engine::GameObject* leftWall = new engine::GameObject();
	leftWall->AddComponent<CollisionComponent>(blockSize, height, false, CollisionLayer::STATIC);
	leftWall->AddComponent<StunComponent>();
	leftWall->AttachTo(walls, false);

	engine::GameObject* rightWall = new engine::GameObject();
	rightWall->SetLocalPosition( width - blockSize, 0);
	rightWall->AddComponent<CollisionComponent>(blockSize, height, false, CollisionLayer::STATIC);
	rightWall->AddComponent<StunComponent>();
	rightWall->AttachTo(walls, false);

	return walls;
}

engine::GameObject* pengo::CreateIceBlock(glm::vec3 position) {
	engine::GameObject* block = CreateBlock("Sprites/ice.png", position, 32, CollisionLayer::STATIC);
	block->AddComponent<SlidingComponent>(200.0f);
	return block;
}