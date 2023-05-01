#pragma once
#include "Component.h"
#include <memory>
#include "Observer.h"

namespace dae {
	class GameObject;
}

class PointComponent;
class TextRenderComponent;

class PointsHUD : public Component, public Observer
{
public:
	PointsHUD(dae::GameObject* pOwner, PointComponent* pHealthComponent);
	virtual ~PointsHUD() = default;

	PointsHUD(const PointsHUD& other) = delete;
	PointsHUD(PointsHUD&& other) = delete;
	PointsHUD& operator=(const PointsHUD& other) = delete;
	PointsHUD& operator=(PointsHUD&& other) = delete;

	virtual void Update([[maybe_unused]] float elapsedSec) {}
	virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

	virtual void OnNotify(EventType event, dae::GameObject* damagedObject) override;

private:
	PointComponent* m_pPointComponent;
	TextRenderComponent* m_pTextRenderer;
};

