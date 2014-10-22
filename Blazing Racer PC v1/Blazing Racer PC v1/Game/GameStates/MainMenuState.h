#pragma once

#ifndef __MAINMENUSTATE__
#define __MAINMENUSTATE__

#include "Game/GameStates/IGameState.h"
#include "Graphics/XSprite.h"

using namespace Graphics;

namespace GameState
{
	class MainMenuState:public IGameState
	{
		XSprite					*m_pSprite;			
	public:
		MainMenuState(void);
		~MainMenuState(void);
		void					Init();
		void					Update();
		void					Render();
		void					Destroy();
	};
}

#endif