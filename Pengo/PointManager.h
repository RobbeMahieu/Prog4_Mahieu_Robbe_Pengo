#pragma once
#include <Singleton.h>
#include <SubjectObserver.h>
#include <vector>


namespace pengo {


	class PointManager final : public engine::Singleton<PointManager>
	{
		public:
			void AddScore(int amount);
			int GetScore();

			engine::Subject<int> ScoreChanged;

		private:
			int m_Score{ 0 };

	};

}

