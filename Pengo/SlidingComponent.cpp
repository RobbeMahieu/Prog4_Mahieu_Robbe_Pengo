#include "SlidingComponent.h"
#include "GameObject.h"
#include "IceBlockState.h"

using namespace pengo;

SlidingComponent::SlidingComponent(engine::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_pState{ new Idle(pOwner, speed)}
{
	// So this component needs to be added after a collision one, could be done better
	m_pOwner->GetComponent<CollisionComponent>()->OnCollision.AddObserver(this);
	m_pOwner->GetComponent<CollisionComponent>()->Collides.AddObserver(this);
}

SlidingComponent::~SlidingComponent() {
	delete m_pState;
}

void SlidingComponent::Update() {
	
	IceBlockState* state = m_pState->Update();
	TransitionTo(state);
}

void SlidingComponent::OnNotify(CollisionComponent* other) {
	
	IceBlockState* state = m_pState->HandleCollision(other);
	TransitionTo(state);
}

void SlidingComponent::TransitionTo(IceBlockState* state) {
	if (state && state != m_pState) {
		delete m_pState;
		m_pState = state;
		m_pState->OnEnter();
	}
}

void SlidingComponent::Push(glm::vec2 direction) {
	IceBlockState* state = m_pState->Push(direction);
	TransitionTo(state);
}

void SlidingComponent::HideEgg() {
	TransitionTo(new Egg(m_pOwner));
}