#pragma once
#include "Component.h"
#include <memory>
#include <SubjectObserver.h>
#include "TextureRenderComponent.h"
#include <string>

namespace pengo {

	class HealthComponent;

	class HealthHUD final : public engine::Component, public engine::Observer<HealthComponent*, int>
	{
		public:
			HealthHUD(engine::GameObject* pOwner, HealthComponent* pHealthComponent, const std::string& iconPath);
			virtual ~HealthHUD() = default;

			HealthHUD(const HealthHUD& other) = delete;
			HealthHUD(HealthHUD&& other) = delete;
			HealthHUD& operator=(const HealthHUD& other) = delete;
			HealthHUD& operator=(HealthHUD&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}

			virtual void OnNotify(HealthComponent* component, int health) override;

		private:
			std::vector<engine::GameObject*> m_Lives;
			std::string m_IconPath;
			void AddLifeIcon();
			void RemoveLifeIcon();
	};
}

