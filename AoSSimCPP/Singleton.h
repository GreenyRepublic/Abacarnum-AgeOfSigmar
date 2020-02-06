#pragma once
#include <memory>

// Just your friendly neighbourhood singleton implementation

template<typename T>
class Singleton
{
public:
	static std::weak_ptr<T> getInstance() 
	{ 
		if (!isInstantiated)
		{
			instance = std::make_shared<T>();
			isInstantiated = true;
		}
		return instance; 
	}

private:
	static std::shared_ptr<T> instance;
	static bool isInstantiated = false;
};

