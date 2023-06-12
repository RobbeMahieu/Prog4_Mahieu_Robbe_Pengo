#include "SnowBee.h"
#include <TextureRenderComponent.h>
#include "CollisionComponent.h"
#include "AIMovement.h"
#include "StickyComponent.h"
#include "KillPlayerComponent.h"

using namespace pengo;

engine::GameObject* pengo::CreateSnowBee(glm::vec3 position) {
	
	auto bee = new engine::GameObject();
	bee->SetLocalPosition(position);
	bee->AddComponent<engine::TextureRenderComponent>("Sprites/snowbee.png");
	bee->AddComponent<CollisionComponent>(32.0f, 32.0f, false, CollisionLayer::ENEMY);
	bee->AddComponent<AIMovement>(50.0f);
	bee->AddComponent<StickyComponent>();
	bee->AddComponent<KillPlayerComponent>();

	return bee;
}