#pragma once

#ifndef __PAUSESTATE__
#define __PAUSESTATE__

#include "Game/GameStates/IGameState.h"
#include "Graphics/XSprite.h"

using namespace Graphics;

namespace GameState
{
	class PauseState:public IGameState
	{
		XSprite					*m_pSprite;
	public:
		PauseState(void);
		~PauseState(void);
		void					Init();
		void					Update();
		void					Render();
		void					Destroy();
	};
}

#endif