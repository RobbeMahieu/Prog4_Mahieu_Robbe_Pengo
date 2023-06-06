#pragma once
#include <vector>
#include "Observer.h"

namespace engine {

	template<typename... Args>
	class Subject final
	{
		public:
			Subject() = default;
			~Subject() = default;

			Subject(const Subject& other) = delete;
			Subject(Subject&& other) = delete;
			Subject& operator=(const Subject& other) = delete;
			Subject& operator=(Subject&& other) = delete;

			void AddObserver(Observer<Args...>* pObserver) {
				m_pObservers.push_back(pObserver);
			}

			void RemoveObserver(Observer<Args...>* pObserver) {
				m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
			}

			void Broadcast(Args... args) {
				for (Observer<Args...>* pObserver : m_pObservers) {
					pObserver->OnNotify(args...);
				}
			}

		private:
			std::vector<Observer<Args...>*> m_pObservers;
	};
}

