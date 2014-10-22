#include "stdafx.h"
#include "Car.h"
#include "Game/World.h"
#include "Sound/XSound/XSound.h"
#include "Network/NetworkManager.h"
#include "UI/Hud.h"

Car::Car(void)
{
	m_pPhysicsActor = nullptr;
	m_Input			= '\0';
	m_PlayerNmber	= -999;
}


Car::~Car(void)
{
	SAFE_DELETE_POINTER(m_pPhysicsActor);
}


void Car:: SpawnCar( int _playerNumber,XMFLOAT3 _pos,XMFLOAT3 _rot,float _height,float _width,IDirect3DTexture9 *_pTex, float _depth)
{
	XMVECTOR _velocity,_acceleration;

	_velocity.x		= 0;
	_velocity.y		= 0;
	_velocity.z		= 0;

	_acceleration.x	= 0;
	_acceleration.y	= 0;
	_acceleration.z	= 0;

	m_PlayerNmber	= _playerNumber;

	m_pPhysicsActor = new PhysicsActor(ASSETTYPE_PLAYER,_pos,_rot,XMFLOAT3(0,0,0),XMFLOAT4(0,0,0,0), _height, _width,_pTex,_depth,_velocity,_acceleration,1,0.9f);

	World::GetInstance()->AddActor(m_pPhysicsActor);
}

void Car::Update()
{
	MoveCar();
}

void Car:: SetInput(char _Input)
{
	m_Input=_Input;
}


void Car:: MoveCar()
{

	if(m_Input & 1)
	{
		XMVECTOR force={0, 100, 0};
		m_pPhysicsActor->GetPhysicsObject()->AddForce(force);

		if(NetworkManager::getInstance()->GetLocalPlayerIndex() == m_PlayerNmber)
		{
			m_pitchLevel += 2;
			if(m_pitchLevel >= MAX_PITCH_LEVEL)
				m_pitchLevel = MAX_PITCH_LEVEL;

			float angle = Hud::GetInstance()->GetMeterRotationFactor();
			angle -= 0.01;
			Hud::GetInstance()->SetMeterRotationFactor(angle);
		}
	}
	else
	{
		if(NetworkManager::getInstance()->GetLocalPlayerIndex() == m_PlayerNmber)
		{
			m_pitchLevel -= 10;
			if(m_pitchLevel <= MIN_PITCH_LEVEL)
				m_pitchLevel = MIN_PITCH_LEVEL;

			float angle = Hud::GetInstance()->GetMeterRotationFactor();
			angle += 0.05;
			Hud::GetInstance()->SetMeterRotationFactor(angle);
		}
	}

	if( m_Input & 2)
	{
		XMVECTOR force={0, -20, 0};
		m_pPhysicsActor->GetPhysicsObject()->AddForce(force);

		if(NetworkManager::getInstance()->GetLocalPlayerIndex() == m_PlayerNmber)
		{
			m_pitchLevel -= 10;
			if(m_pitchLevel <= MIN_PITCH_LEVEL)
				m_pitchLevel = MIN_PITCH_LEVEL;

			float angle = Hud::GetInstance()->GetMeterRotationFactor();
			angle += 0.05;
			Hud::GetInstance()->SetMeterRotationFactor(angle);
		}
	}

	if(m_Input & 4)
	{
		XMVECTOR force={-40, 0, 0};
		m_pPhysicsActor->GetPhysicsObject()->AddForce(force);
	}

	if(m_Input & 8)
	{
		XMVECTOR force={40, 0, 0};
		m_pPhysicsActor->GetPhysicsObject()->AddForce(force);
	}

	if(m_Input & 32)
	{
		//NOS
		m_pPhysicsActor->GetPhysicsObject()->ApplyNOS();
		float angle = Hud::GetInstance()->GetMeterRotationFactor();
		angle -= 0.05;
		Hud::GetInstance()->SetMeterRotationFactor(angle);
	}
}
