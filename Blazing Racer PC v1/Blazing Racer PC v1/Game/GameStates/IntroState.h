#pragma once

#ifndef __INTROSTATE__
#define __INTROSTATE__

#include "Game/GameStates/IGameState.h"
#include "Graphics/XSprite.h"

using namespace Graphics;

namespace GameState
{

	class IntroState:public IGameState
	{
		XSprite				*m_pSprite;
	public:
		IntroState(void);
		~IntroState(void);

		void				Init();
		void				Update();
		void				Render();
		void				Destroy();
	};

}
#endif