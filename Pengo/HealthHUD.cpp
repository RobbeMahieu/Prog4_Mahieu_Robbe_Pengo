#include "HealthHUD.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "HealthComponent.h"

using namespace pengo;

HealthHUD::HealthHUD(engine::GameObject* pOwner, HealthComponent* pHealthComponent, const std::string& iconPath)
	: Component(pOwner)
	, m_IconPath{ iconPath}
{
	pHealthComponent->HealthChanged.AddObserver(this);

	for (int i{ 0 }; i < pHealthComponent->GetHealth(); ++i) {
		AddLifeIcon();
	}

}

void HealthHUD::OnNotify(HealthComponent* /*component*/, int amount) {
	
	while (m_Lives.size() != amount && amount >= 0) {

		if (m_Lives.size() < amount) {
			AddLifeIcon();
		}
		else {
			RemoveLifeIcon();
		}
	}
}

void HealthHUD::AddLifeIcon() {
	engine::GameObject* life{ new engine::GameObject() };
	life->AddComponent<engine::TextureRenderComponent>(m_IconPath);
	life->SetLocalPosition(glm::vec3{ m_Lives.size() * 20,0,0 });
	life->AttachTo(m_pOwner, false);
	m_Lives.push_back(life);
}

void HealthHUD::RemoveLifeIcon() {
	m_Lives[m_Lives.size()-1]->Destroy();
	m_Lives.erase(std::remove(m_Lives.begin(), m_Lives.end(), m_Lives[m_Lives.size() - 1]), m_Lives.end());
}