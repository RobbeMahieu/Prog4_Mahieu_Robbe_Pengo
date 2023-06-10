#include "SnowBee.h"
#include <TextureRenderComponent.h>
#include "CollisionComponent.h"
#include "AIMovement.h"

using namespace pengo;

engine::GameObject* pengo::CreateSnowBee(glm::vec3 position) {
	
	auto bee = new engine::GameObject();
	bee->SetLocalPosition(position);
	bee->AddComponent<engine::TextureRenderComponent>("snowbee.png");
	bee->AddComponent<CollisionComponent>(32.0f, 32.0f, false, PhysicsType::DYNAMIC);
	bee->AddComponent<AIMovement>(50.0f);

	return bee;
}