#pragma once

#ifndef __NEWGAMESTATE__
#define __NEWGAMESTATE__

#include "Game/GameStates/IGameState.h"
#include "Graphics/XSprite.h"

using namespace Graphics;

namespace GameState
{

class NewGameState:public IGameState
{
	XSprite					*m_pSprite;
public:
	NewGameState(void);
	~NewGameState(void);
	void					Init();
	void					Update();
	void					Render();
	void					Destroy();
};
}
#endif