#pragma once
#include "Component.h"
#include <memory>
#include <SubjectObserver.h>
#include "TextRenderComponent.h"

namespace pengo {

	class PointComponent;

	class PointsHUD : public engine::Component, public engine::Observer<int>
	{
		public:
			PointsHUD(engine::GameObject* pOwner, PointComponent* pPointComponent);
			virtual ~PointsHUD() = default;

			PointsHUD(const PointsHUD& other) = delete;
			PointsHUD(PointsHUD&& other) = delete;
			PointsHUD& operator=(const PointsHUD& other) = delete;
			PointsHUD& operator=(PointsHUD&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}

			virtual void OnNotify(int score) override;

		private:
			engine::TextRenderComponent* m_pTextRenderer;
	};

}
