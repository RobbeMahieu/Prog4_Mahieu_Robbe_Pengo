#include "SlidingComponent.h"
#include <GameObject.h>
#include "IceBlockState.h"
#include <TextureRenderComponent.h>

using namespace pengo;

SlidingComponent::SlidingComponent(engine::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_pState{ new Idle(this)}
	, m_Speed{ speed }
	, m_IsDiamond{ false }
	, m_IsEgg{ false }
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
	m_IsEgg = true;
	m_pOwner->GetComponent<engine::TextureRenderComponent>()->SetTexture("egg.png");
}

void SlidingComponent::SetDiamond() {
	m_IsDiamond = true;
	m_pOwner->GetComponent<engine::TextureRenderComponent>()->SetTexture("diamond.png");
}

bool SlidingComponent::IsEgg() const {
	return m_IsEgg;
}

bool SlidingComponent::IsDiamond() const {
	return m_IsDiamond;
}