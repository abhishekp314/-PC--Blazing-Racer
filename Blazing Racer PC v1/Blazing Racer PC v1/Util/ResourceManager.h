#pragma once
#ifndef		__RESOURCE_MANAGER_
#define		__RESOURCE_MANAGER_
#include <string>
#include <map>
#include "IResource.h"


namespace Util
{
	using namespace std;

	class ResourceManager
	{
	private:
		static ResourceManager*		m_pResourceManagerInstance;
		ResourceManager(void);

		map<string,IResource*>		m_resourcesMap;

	public:
		~ResourceManager(void);
		static ResourceManager*		GetInstance();

		template<class T>
		T* Load(const char* filename)
		{
			T *t = new T();
			if(FAILED(t->Load(filename)))
			{
				string ErrorString = "\nERROR Could Not Find Resource :";
				ErrorString.append(filename);
				ErrorString.append("\n");
				
				OutputDebugString(ErrorString.c_str());
			}

			return t;
		}

		IResource*					GetResource(const char* resourceName);
	};
}
#endif

