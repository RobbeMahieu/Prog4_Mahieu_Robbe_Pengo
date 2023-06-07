#include "CollisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "GameTime.h"

using namespace pengo;

std::vector<CollisionComponent*> CollisionComponent::m_pColliders{};

CollisionComponent::CollisionComponent(engine::GameObject* pOwner, int width, int height, bool trigger, PhysicsType type)
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