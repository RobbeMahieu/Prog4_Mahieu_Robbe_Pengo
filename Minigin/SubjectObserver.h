#pragma once
#include <vector>

namespace engine {

	template<typename... Args>
	class Observer;

	template<typename... Args>
	class Subject final
	{
		public:
			Subject() = default;
			virtual ~Subject();

			Subject(const Subject& other) = delete;
			Subject(Subject&& other) = delete;
			Subject& operator=(const Subject& other) = delete;
			Subject& operator=(Subject&& other) = delete;

			void AddObserver(Observer<Args...>* pObserver);
			void RemoveObserver(Observer<Args...>* pObserver);
			void Broadcast(Args... args);

		private:
			std::vector<Observer<Args...>*> m_pObservers;
	};

	template<typename... Args>
	class Observer
	{
		public:
			explicit Observer() = default;
			virtual ~Observer();

			Observer(const Observer& other) = delete;
			Observer(Observer&& other) = delete;
			Observer& operator=(const Observer& other) = delete;
			Observer& operator=(Observer&& other) = delete;

			virtual void OnNotify(Args... args) = 0;

		private:
			// Only used for unregistering when it gets destroyed
			friend class Subject<Args...>;
			std::vector<Subject<Args...>*> m_pRegisteredSubjects;
	};

	// -- Subject implementations
	template<typename... Args>
	void Subject<Args...>::AddObserver(Observer<Args...>* pObserver) {
		m_pObservers.push_back(pObserver);
		pObserver->m_pRegisteredSubjects.push_back(this);
	}

	template<typename... Args>
	void Subject<Args...>::RemoveObserver(Observer<Args...>* pObserver) {
		m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
	}

	template<typename... Args>
	void Subject<Args...>::Broadcast(Args... args) {
		for (Observer<Args...>* pObserver : m_pObservers) {
			pObserver->OnNotify(args...);
		}
	}

	template<typename... Args>
	Subject<Args...>::~Subject() {
		for (Observer<Args...>* pObserver : m_pObservers) {
			// Remove from the registered list
			pObserver->m_pRegisteredSubjects.erase(std::remove(pObserver->m_pRegisteredSubjects.begin(), pObserver->m_pRegisteredSubjects.end(), this), pObserver->m_pRegisteredSubjects.end());
		}
	};


	// -- Observer implementations
	template<typename... Args>
	Observer<Args...>::~Observer() {
		for (Subject<Args...>* subject : m_pRegisteredSubjects) {
			subject->RemoveObserver(this);
		}
	};
}

