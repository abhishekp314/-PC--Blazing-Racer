#pragma once

#ifndef __IGAMESTATE__
#define __IGAMESTATE__


namespace GameState
{

	class IGameState
	{
	protected:
		BOOL m_isPaused;
	public:
		IGameState(void);
		~IGameState(void);

		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void Destroy();
		BOOL		 GetPauseState()		{ return m_isPaused; }
	};

}
#endif