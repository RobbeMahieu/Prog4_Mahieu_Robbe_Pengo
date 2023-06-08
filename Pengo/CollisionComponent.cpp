#include "CollisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "GameTime.h"

using namespace pengo;

std::vector<CollisionComponent*> CollisionComponent::m_pColliders{};

CollisionComponent::CollisionComponent(engine::GameObject* pOwner, float width, float height, bool trigger, PhysicsType type)
	: Component(pOwner)
	, m_Width{ width }
	, m_Height{ height }
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

	for (CollisionComponent* other : m_pColliders) {

		if (other == this) {
			continue;
		}

		glm::vec3 otherPos{ other->m_pOwner->GetWorldPosition() };

		float differenceLeft{ pos.x - otherPos.x - other->m_Width };
		float differenceRight{ pos.x + m_Width - otherPos.x };
		float differenceTop{ pos.y - otherPos.y - other->m_Height };
		float differenceBottom{ pos.y + m_Height - otherPos.y };

		if (differenceBottom < 0
			|| differenceTop > 0
			|| differenceLeft > 0
			|| differenceRight < 0) {

			// Remove from colliding list
			if (m_pColliding.contains(other)) {
				m_pColliding.erase(other);
				EndCollision.Broadcast(other);
				other->m_pColliding.erase(other);
				other->EndCollision.Broadcast(this);
			}

			continue;
		}

		// Resolve positions
		if (m_IsTrigger || other->m_IsTrigger 
			||(m_Type == PhysicsType::STATIC && other->m_Type == PhysicsType::STATIC)) {
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

		glm::vec3 diff{};
		diff.x = (abs(differenceLeft) < abs(differenceRight)) ? differenceLeft : differenceRight;
		diff.y = (abs(differenceTop) < abs(differenceBottom)) ? differenceTop : differenceBottom;
		glm::vec3 offset{ abs(diff.x) < abs(diff.y) ? glm::vec3{ diff.x, 0, 0 } : glm::vec3{ 0, diff.y, 0 } };
		offset = (getsMoved && otherGetsMoved) ? offset * 0.5f : offset;

		// Rounding
		offset.x = offset.x > 0 ? ceil(offset.x) : floor(offset.x);
		offset.y = offset.y > 0 ? ceil(offset.y) : floor(offset.y);

		if (getsMoved) {
			m_pOwner->SetLocalPosition(pos - offset);
		}

		if (otherGetsMoved) {
			other->m_pOwner->SetLocalPosition(otherPos + offset);
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

bool CollisionComponent::CheckCollision(CollisionComponent* collider, std::vector<CollisionComponent*> toIgnore) {
	
	glm::vec3 pos{ collider->m_pOwner->GetWorldPosition() };
	toIgnore.emplace_back(collider);

	return CheckCollision(pos.x, pos.y, collider->m_Width, collider->m_Height, toIgnore);
}

bool CollisionComponent::CheckCollision(glm::vec4 bounds, std::vector<CollisionComponent*> toIgnore) {

	return CheckCollision(bounds.x, bounds.y, bounds.z, bounds.w, toIgnore);
}

bool CollisionComponent::CheckCollision(float x, float y, float width, float height, std::vector<CollisionComponent*> toIgnore) {
	for (CollisionComponent* collider : m_pColliders) {

		// Ignore this collider
		if (std::find(toIgnore.begin(), toIgnore.end(), collider) != toIgnore.end()) {
			continue;
		}

		glm::vec3 pos{ collider->m_pOwner->GetWorldPosition() };

		float differenceLeft{ x - pos.x - collider->m_Width };
		float differenceRight{ x + width - pos.x };
		float differenceTop{ y - pos.y - collider->m_Height };
		float differenceBottom{ y + height - pos.y };

		// No collision, continue search
		if (differenceBottom < 0
			|| differenceTop > 0
			|| differenceLeft > 0
			|| differenceRight < 0) {

			continue;
		}

		// Collision has happened!
		return true;
	}

	// Couldn't find any collision
	return false;
}

glm::vec4 CollisionComponent::GetBounds() const {

	glm::vec2 pos{ m_pOwner->GetWorldPosition() };
	return glm::vec4{ pos.x, pos.y, m_Width, m_Height };
}