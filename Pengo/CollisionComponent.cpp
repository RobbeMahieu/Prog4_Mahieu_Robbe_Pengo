#include "CollisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"

std::vector<CollisionComponent*> CollisionComponent::m_pColliders{};

CollisionComponent::CollisionComponent(dae::GameObject* pOwner, float width, float height, bool solid, bool movable)
	: Component(pOwner)
	, m_Width{ width }
	, m_Height{ height }
	, m_IsSolid{ solid }
	, m_IsMovable{ movable }
{
	m_pColliders.push_back(this);
}

CollisionComponent::~CollisionComponent() {
	m_pColliders.erase(std::remove(m_pColliders.begin(), m_pColliders.end(), this), m_pColliders.end());
}

void CollisionComponent::FixedUpdate(float /*elapsedSec*/) {

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
			}

			continue;
		}

		// Resolve Events
		if (m_pColliding.contains(other)) {
			Collides.Broadcast(other);
		}
		else {
			m_pColliding.insert(other);
			OnCollision.Broadcast(other);
		}

		// Resolve positions
		if (m_IsSolid && other->m_IsSolid && (m_IsMovable || other->m_IsMovable) ) {

			glm::vec3 diff{};
			diff.x = (abs(differenceLeft) < abs(differenceRight)) ? ceil(differenceLeft) : ceil(differenceRight);
			diff.y = (abs(differenceTop) < abs(differenceBottom)) ? ceil(differenceTop) : ceil(differenceBottom);

			glm::vec3 offset{ abs(diff.x) < abs(diff.y) ? glm::vec3{ diff.x, 0, 0 } : glm::vec3{ 0, diff.y, 0 } };
			offset = (m_IsMovable && other->m_IsMovable) ? offset * 0.5f : offset;

			if (m_IsMovable) {
				m_pOwner->SetLocalPosition(pos - offset);
			}

			if (other->m_IsMovable) {
				other->m_pOwner->SetLocalPosition(otherPos + offset);
			}
		}
	}
}

void CollisionComponent::Render() const {
	// For debug purposes
	/*glm::vec3 pos{m_pOwner->GetWorldPosition()};
	SDL_Rect rectangle{ int(pos.x), int(pos.y), int(m_Width), int(m_Height) };
	SDL_Color drawColor{ 0,0,255,255 };
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), drawColor.r, drawColor.g, drawColor.b, drawColor.a);
	SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &rectangle);*/
}

const std::unordered_set<CollisionComponent*> CollisionComponent::GetColliding() const {
	return m_pColliding;
}