#pragma once

#include "Game/GameActors/IActor.h"
#include<vector>

using namespace std;

class LevelLoader
{
	static LevelLoader	*ms_pLevelLoader;

	LevelLoader()
	{

	}

public:
	
	static LevelLoader*		 GetInstance();
	~LevelLoader(void);

	void				LoadLevel(char *_pLevelFilename);
};

