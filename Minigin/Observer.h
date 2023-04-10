#pragma once
#include <functional>

namespace dae {
	class GameObject;
}

class Observer
{
	public:
		explicit Observer(const std::function<void(dae::GameObject*)>& function);

		~Observer();

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		void Execute(dae::GameObject* invokingObject);

	private:
		std::function<void(dae::GameObject*)> m_Function;
};

