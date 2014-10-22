#include "stdafx.h"
#include "Util/Util.h"
#include "Game/XPhysics.h"

using namespace Util;

extern TimeInfo	g_Time;


XPhysics::XPhysics(XMVECTOR _position, XMVECTOR _velocity, XMVECTOR _acceleration, float _mass, float _damping)
{
	this->m_Position	 = _position;
	this->m_Velocity	 = _velocity;
	this->m_Acceleration = _acceleration;
	this->m_Mass		 = _mass;
	this->m_Damping		 = _damping;
	this->m_NOSFuel		 = 0;

	if(_mass >= 999)
	{
		SetInverseMass(0);
		_mass = 1;
	}
	else
		this->m_InverseMass	 = 1 / m_Mass;

	m_ForceAccumulator	 = Float3ToVec(XMFLOAT3(0,0,0));

	m_ContactNormal		 = Float3ToVec(XMFLOAT3(0,-1,0));
}

XPhysics::~XPhysics()
{

}

void XPhysics::AddForce(XMVECTOR _newForce)
{
	m_ForceAccumulator += _newForce;
}

void XPhysics::Integrator()
{
	XMVECTOR currentAcceleration = m_Acceleration;

	//GET DELTA TIME HERE
	float dt = g_Time.fElapsedTime * 6;

	//Update the position
	m_Position += (m_Velocity*dt);

	//Update the Resulting Acceleration
	currentAcceleration += m_ForceAccumulator * dt;

	//Update linear Velocity
	m_Velocity += currentAcceleration * dt;

	//Impose Draging force
	m_Velocity *= (float)pow( m_Damping, dt);
}

void XPhysics::ClearForce()
{
	m_ForceAccumulator.x = 0;
	m_ForceAccumulator.y = 0;
	m_ForceAccumulator.z = 0;
}

BOOL XPhysics::HasFiniteMass()
{
	return m_InverseMass >= 0.0f;
}

float XPhysics::GetMass()
{
	if(m_InverseMass == 0)
		return 0.0f;
	else
		return 1/m_InverseMass;

}


void XPhysics::ApplyNOS()
{
	if(m_NOSFuel <= 0)
		m_NOSFuel = 0;
	else
	{
		m_NOSFuel--;
		AddForce(Float3ToVec(XMFLOAT3(0, 50, 0)));
	}
}