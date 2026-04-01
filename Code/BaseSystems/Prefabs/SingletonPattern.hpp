/******************************************************************************/
/*!
\file   SingletonPattern.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the template to store single instance of a class
*/
/******************************************************************************/
#pragma once
#include <iostream>

template <typename T>

class SingletonPattern
{
private:
	static T* instance;		//Empty address of template

public:
/*!***********************************************************************
\brief Gets instance of template class. Gets and return instance. 
	   If instance is null, create new template.
\return template<T>
*************************************************************************/
	static T* GetInstance(void)
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

/*!***********************************************************************
\brief Delete instance of template class. If instance is not null, 
		deletes instance of template class and set instance back to null
\return template<T>
*************************************************************************/
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