#include "IceBlockState.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "PushComponent.h"
#include "GameTime.h"
#include "TextureRenderComponent.h"
#include "EnemySpawner.h"
#include "SlidingComponent.h"
#include <GameServiceLocator.h>

using namespace pengo;

// -- Base State --
IceBlockState::IceBlockState(SlidingComponent* component)
	: m_pIce{ component }
{
}

// -- Sliding State --

Sliding::Sliding(SlidingComponent* component, const glm::vec2& direction)
	: IceBlockState(component)
	, m_Direction{direction}
{
}

void Sliding::OnEnter() {
	CollisionComponent* collider = m_pIce->m_pOwner->GetComponent<CollisionComponent>();
	collider->SetLayer(CollisionLayer::DYNAMIC);

	// Push sound
	engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/push.wav", 0.5f);
}

IceBlockState* Sliding::Update() {
	const float elapsedSec{ engine::GameTime::GetInstance().GetElapsedSec() };

	glm::vec3 pos = m_pIce->m_pOwner->GetLocalPosition();
	pos.x += m_pIce->m_Speed * elapsedSec * m_Direction.x;
	pos.y += m_pIce->m_Speed * elapsedSec * m_Direction.y;
	m_pIce->m_pOwner->SetLocalPosition(pos);

	return nullptr;
}

IceBlockState* Sliding::HandleCollision(CollisionComponent* collider) {
	return (collider->GetLayer() == CollisionLayer::STATIC) ? new Idle(m_pIce) : nullptr;
}

// Idle State --

Idle::Idle(SlidingComponent* component)
	: IceBlockState(component)
{
}

void Idle::OnEnter() {
	CollisionComponent* collider = m_pIce->m_pOwner->GetComponent<CollisionComponent>();
	collider->SetLayer(CollisionLayer::STATIC);
}

IceBlockState* Idle::Push(glm::vec2 direction) {
	
	if (m_pIce->IsEgg()) {

		// Egg sound
		engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/eggDestroyed.wav", 0.5f);

		return new Break(m_pIce);
	}

	CollisionComponent* collider = m_pIce->m_pOwner->GetComponent<CollisionComponent>();
	glm::vec3 pos{ m_pIce->GetOwner()->GetLocalPosition() };
	pos.x += direction.x * 1;
	pos.y += direction.y * 1;
	m_pIce->m_pOwner->SetLocalPosition(pos);


	// Check for collision in moving direction
	CollisionHit hitResult{ collider->CheckCollision( {}, {CollisionLayer::STATIC, CollisionLayer::DYNAMIC})};
	pos.x -= direction.x * 1;
	pos.y -= direction.y * 1;
	m_pIce->m_pOwner->SetLocalPosition(pos);


	// Start break
	if (hitResult.hit) {
		// Break sound
		engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/break.wav", 0.5f);

		return new Break(m_pIce);
	}
	// Start push
	return new Sliding(m_pIce, direction);

}

// -- Break State --
Break::Break(SlidingComponent* component)
	: IceBlockState(component)
{
}

IceBlockState* Break::Update() {
	
	if (!m_pIce->IsDiamond()) {
		m_pIce->m_pOwner->GetComponent<SlidingComponent>()->m_Broken.Broadcast(m_pIce);
		m_pIce->m_pOwner->Destroy();
	}
	
	return nullptr;
}