#pragma once

#ifndef __GAMEOVER__
#define __GAMEOVER__

#include "IGameState.h"

namespace GameState
{

		class GameOver : public IGameState
		{
				
			public:
				GameOver(void);
				~GameOver(void);

				void					Init();
				void					Update();
				void					Render();
				void					Destroy();				
		};

}

#endif