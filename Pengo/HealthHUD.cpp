#include "HealthHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "HealthComponent.h"

using namespace pengo;

HealthHUD::HealthHUD(engine::GameObject* pOwner, HealthComponent* pHealthComponent)
	: Component(pOwner)
	, m_pTextRenderer{ pOwner->GetComponent<engine::TextRenderComponent>() }
{
	pHealthComponent->HealthChanged.AddObserver(this);
	OnNotify(pHealthComponent->GetHealth());
}

void HealthHUD::OnNotify(int amount) {
	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Lives: " + std::to_string(amount));
	}
}