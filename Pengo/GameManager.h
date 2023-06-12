#pragma once
#include <Component.h>
#include <GameObject.h>
#include <SubjectObserver.h>
#include <memory>

namespace pengo {

	class GameState;
	class FunctionCommand;
	
	class GameManager final : public engine::Component
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

			void ToggleSound();

		private:
			GameState* m_pState;

			// Music
			std::unique_ptr<FunctionCommand> m_ToggeSound;
			bool m_MusicStarted;
			bool m_IsMuted;

			void TransitionTo(GameState* state);
	};
}
