#pragma once
#ifndef __CAR_
#define __CAR_

#include "Game/GameActors/PhysicsActor.h"

	class Car
	{
	private:
		PhysicsActor*	m_pPhysicsActor;
		char			m_Input;
		int				m_PlayerNmber;
		short			m_pitchLevel;

	public:
		Car(void);
		~Car(void);

		void			SpawnCar( int _playerNumber,XMFLOAT3 _pos,XMFLOAT3 _rot,float _height,float _width,IDirect3DTexture9 *_pTex, float _depth);
		void			MoveCar();
		void			Update();
		void			SetInput(char _Input);
		PhysicsActor*	GetPhysicsActor() {return m_pPhysicsActor;}

	};


#endif