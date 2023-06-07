#pragma once
#include "Singleton.h"
#include <chrono>

namespace engine {

	class GameTime : public Singleton<GameTime>
	{
		public:
			void Init();
			void Update();

			float GetElapsedSec() const;
			float GetTotalSec() const;
			std::chrono::steady_clock::time_point GetFrameStartTime() const;
			float GetFixedUpdateStep() const;

		private:

			float m_FixedUpdateStep;
			float m_DeltaTime;
			std::chrono::steady_clock::time_point m_StartTime;
			std::chrono::steady_clock::time_point m_LastFrameTime;
	};
}



