#pragma once
#include "Component.h"
#include "Subject.h"

namespace pengo {

	class PointComponent final : public engine::Component
	{
	public:
		PointComponent(engine::GameObject* pOwner);
		virtual ~PointComponent() = default;

		PointComponent(const PointComponent& other) = delete;
		PointComponent(PointComponent&& other) = delete;
		PointComponent& operator=(const PointComponent& other) = delete;
		PointComponent& operator=(PointComponent&& other) = delete;

		virtual void Update() override {}
		virtual void FixedUpdate() override{}

		void AddScore(int amount);
		int GetScore();

	private:
		int m_Score;

		void SetScore(int newScore);

	public:
		engine::Subject<int> ScoreChanged;
	};

}

