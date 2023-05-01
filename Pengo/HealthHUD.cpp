#include "HealthHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "HealthComponent.h"

HealthHUD::HealthHUD(dae::GameObject* pOwner, HealthComponent* pHealthComponent)
	: Component(pOwner)
	, m_pTextRenderer{ pOwner->GetComponent<TextRenderComponent>() }
{
	pHealthComponent->HealthChanged.AddObserver(this);
	OnNotify(pHealthComponent->GetHealth());
}

void HealthHUD::OnNotify(int amount) {
	if (m_pTextRenderer) {
		m_pTextRenderer->SetText("Lives: " + std::to_string(amount));
	}
}