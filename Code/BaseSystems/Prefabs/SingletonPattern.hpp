/*!
@file SingletonPattern.h
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 12/1/26
@brief
This file contains the template to store single instance of a class
*//*______________________________________________________________________*/
#pragma once
#include <iostream>

template <typename T>

class SingletonPattern
{
private:
	static T* instance;		//Empty address of template

public:
	/*!
	@brief Gets instance of template class

	Gets and return instance. If instance is null, create new template.

	@param void
	@return template<T>
	*//*______________________________________________________________*/
	static T* GetInstance(void)
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

	/*!
	@brief Delete instance of template class

	If instance is not null, deletes instance of template class and set instance back to null

	@param void
	@return template<T>
	*//*______________________________________________________________*/
	static void DestroyInstance(void)
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

template <typename T>
T* SingletonPattern<T>::instance = nullptr;