#pragma once
#include <Component.h>
#include <GameObject.h>
#include <SubjectObserver.h>

namespace pengo {

	class GameState;
	
	class GameManager : public engine::Component
	{
		public:
			GameManager(engine::GameObject* pOwner);
			virtual ~GameManager();

			GameManager(const GameManager& other) = delete;
			GameManager(GameManager&& other) = delete;
			GameManager& operator=(const GameManager& other) = delete;
			GameManager& operator=(GameManager&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {}

		private:
			GameState* m_pState;

			void TransitionTo(GameState* state);
	};
}
