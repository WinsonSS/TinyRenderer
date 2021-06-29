#pragma once
template<typename T>
class Singleton
{
private:
	static T* instance_;
	Singleton() {}

public:
	static T* GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new T();
		}
		return instance_;
	}
};

template<typename T>
T* Singleton<T>::instance_ = nullptr;
