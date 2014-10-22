#include "stdafx.h"
#include "ResourceManager.h"
namespace Util
{
	ResourceManager* ResourceManager::m_pResourceManagerInstance = nullptr;

	ResourceManager::ResourceManager(void)
	{
		
	}


	ResourceManager::~ResourceManager(void)
	{
	}

	ResourceManager* ResourceManager::GetInstance()
	{
		if(!m_pResourceManagerInstance)
		{
			m_pResourceManagerInstance = new ResourceManager();
		}

		return m_pResourceManagerInstance;
	}



	IResource* ResourceManager:: GetResource(const char* resourceName)
	{
 		map<string,IResource*>::iterator it=m_resourcesMap.find(resourceName);
 		return (*it).second;
	}
}

