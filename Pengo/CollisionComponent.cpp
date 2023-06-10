#include "CollisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "GameTime.h"

using namespace pengo;

std::vector<CollisionComponent*> CollisionComponent::m_pColliders{};

CollisionComponent::CollisionComponent(engine::GameObject* pOwner, float width, float height, bool trigger, PhysicsType type)
	: Component(pOwner)
	, m_Width{ width-1 }
	, m_Height{ height-1 }
	, m_IsTrigger{ trigger }
	, m_Type{ type }
{
	m_pColliders.push_back(this);
}

CollisionComponent::~CollisionComponent() {
	m_pColliders.erase(std::remove(m_pColliders.begin(), m_pColliders.end(), this), m_pColliders.end());
}

void CollisionComponent::FixedUpdate() {

	// Statics don't move, so don't need to check collisions
	// Their events will still be call thanks to the other object on collision
	if (m_Type == PhysicsType::STATIC) {
		return;
	}

	glm::vec3 pos{ m_pOwner->GetWorldPosition() };
	CollisionHit hitResult{};

	for (CollisionComponent* other : m_pColliders) {

		// Don't check yourself
		if (other == this) {
			continue;
		}

		// Get collision information
		hitResult = CollidesWith(other);

		// No hit => remove for your collider list (if needed)
		// And resolve events
		if (!hitResult.hit) {
			
			if (m_pColliding.contains(other)) {
				m_pColliding.erase(other);
				EndCollision.Broadcast(other);
				other->m_pColliding.erase(other);
				other->EndCollision.Broadcast(this);
			}

			continue;
		}

		// Did hit!

		// Resolve positions
		if (m_IsTrigger || other->m_IsTrigger
			|| (m_Type == PhysicsType::STATIC && other->m_Type == PhysicsType::STATIC)) {
			continue;
		}

		// Maybe use some kind of collision matrix for this?
		bool getsMoved{
			!(
				m_Type == PhysicsType::STATIC ||
				m_Type == PhysicsType::MOVABLE && other->m_Type == PhysicsType::DYNAMIC
			)
		};

		bool otherGetsMoved{
			!(
				other->m_Type == PhysicsType::STATIC ||
				other->m_Type == PhysicsType::MOVABLE && m_Type == PhysicsType::DYNAMIC
			)
		};

		if (getsMoved && otherGetsMoved) {
			hitResult.offset /= 2;

		}

		// Rounding
		hitResult.offset.x = hitResult.offset.x > 0 ? ceil(hitResult.offset.x) : floor(hitResult.offset.x);
		hitResult.offset.y = hitResult.offset.y > 0 ? ceil(hitResult.offset.y) : floor(hitResult.offset.y);

		if (getsMoved) {
			m_pOwner->SetWorldPosition(pos - hitResult.offset);
		}

		if (otherGetsMoved) {
			other->m_pOwner->SetWorldPosition(other->m_pOwner->GetWorldPosition() + hitResult.offset);
		}

		// Resolve Events
		if (m_pColliding.contains(other)) {
			Collides.Broadcast(other);
			other->Collides.Broadcast(this);
		}
		else {
			m_pColliding.insert(other);
			OnCollision.Broadcast(other);
			other->m_pColliding.insert(this);
			other->OnCollision.Broadcast(this);
		}
	}
}

void CollisionComponent::Render() const {
	// For debug purposes
	glm::vec3 pos{m_pOwner->GetWorldPosition()};
	SDL_Rect rectangle{ int(pos.x), int(pos.y), int(m_Width), int(m_Height) };
	SDL_Color drawColor{ 0,0,255,255 };

	switch (m_Type) {
		case PhysicsType::STATIC:
			drawColor = SDL_Color(255, 0, 0, 255);
			break;
		case PhysicsType::MOVABLE:
			drawColor = SDL_Color(0, 0, 255, 255);
			break;
		case PhysicsType::DYNAMIC:
			drawColor = SDL_Color(0, 255, 0, 255);
			break;
	}

	SDL_SetRenderDrawColor(engine::Renderer::GetInstance().GetSDLRenderer(), drawColor.r, drawColor.g, drawColor.b, drawColor.a);
	SDL_RenderDrawRect(engine::Renderer::GetInstance().GetSDLRenderer(), &rectangle);
}

const std::unordered_set<CollisionComponent*> CollisionComponent::GetColliding() const {
	return m_pColliding;
}

PhysicsType CollisionComponent::GetType() const {
	return m_Type;
}

void CollisionComponent::SetType(PhysicsType type) {
	m_Type = type;
}

CollisionHit CollisionComponent::CheckCollision(CollisionComponent* collider, std::vector<CollisionComponent*> toIgnore) {
	
	glm::vec3 pos{ collider->m_pOwner->GetWorldPosition() };
	toIgnore.emplace_back(collider);

	CollisionHit closestHitResult{};
	float closestDistance{FLT_MAX};

	for (CollisionComponent* other : m_pColliders) {
		
		// Ignore this collider
		if (std::find(toIgnore.begin(), toIgnore.end(), other) != toIgnore.end()) {
			continue;
		}

		// Only return the closest hit
		CollisionHit hitResult = collider->CollidesWith(other);
		if (hitResult.hit && hitResult.distance < closestDistance) { 
			closestHitResult = hitResult;
			closestDistance = hitResult.distance;
		}
	}

	return closestHitResult;
}

CollisionHit CollisionComponent::CheckCollision(glm::vec4 bounds, std::vector<CollisionComponent*> toIgnore) {

	return CheckCollision(bounds.x, bounds.y, bounds.z, bounds.w, toIgnore);
}

CollisionHit CollisionComponent::CheckCollision(float x, float y, float width, float height, std::vector<CollisionComponent*> toIgnore) {
	
	// Create temporary collision component
	engine::GameObject* object{};
	object->SetLocalPosition(x, y);
	CollisionComponent* collider = object->AddComponent<CollisionComponent>(width, height);

	CollisionHit hitResult{ CheckCollision(collider) };

	// Delete temp component
	delete object;
	
	return hitResult;
}

CollisionHit CollisionComponent::CollidesWith(CollisionComponent* other) {

	CollisionHit hitResult{};

	glm::vec3 pos{ m_pOwner->GetWorldPosition() };
	glm::vec3 otherPos{ other->m_pOwner->GetWorldPosition() };

	float differenceLeft{ pos.x - otherPos.x - other->m_Width };
	float differenceRight{ pos.x + m_Width - otherPos.x };
	float differenceTop{ pos.y - otherPos.y - other->m_Height };
	float differenceBottom{ pos.y + m_Height - otherPos.y };

	// No collision
	if (differenceBottom <= 0
		|| differenceTop >= 0
		|| differenceLeft >= 0
		|| differenceRight <= 0) {

		return hitResult;
	}

	// Collision has happened!
	glm::vec3 diff{};
	diff.x = (abs(differenceLeft) < abs(differenceRight)) ? differenceLeft : differenceRight;
	diff.y = (abs(differenceTop) < abs(differenceBottom)) ? differenceTop : differenceBottom;
	glm::vec3 offset{ abs(diff.x) < abs(diff.y) ? glm::vec3{ diff.x, 0, 0 } : glm::vec3{ 0, diff.y, 0 } };

	hitResult.hit = true;
	hitResult.object = other->m_pOwner;
	hitResult.collider = other;
	hitResult.offset = offset;
	hitResult.distance = glm::distance(pos, otherPos);

	return hitResult;
}

glm::vec4 CollisionComponent::GetBounds() const {

	glm::vec2 pos{ m_pOwner->GetWorldPosition() };
	return glm::vec4{ pos.x, pos.y, m_Width, m_Height };
}