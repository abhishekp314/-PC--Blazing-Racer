#pragma once

#ifndef __XPHY__
#define __XPHY__

#include<xnamath.h>
#include<math.h>
#include<limits>

using namespace std;

const float MAX_NOS = 100;

class XPhysics
{
	XMVECTOR		m_Velocity;
	XMVECTOR		m_Position;
	XMVECTOR		m_Acceleration;
	XMVECTOR		m_ForceAccumulator;
	XMVECTOR		m_GAcceleration;
	XMVECTOR		m_ContactNormal;

	float			m_Damping;
	float			m_InverseMass;
	float			m_Mass;

	float			m_NOSFuel;

public:
	XPhysics( XMVECTOR _position, XMVECTOR _velocity, XMVECTOR _acceleration, float _mass, float _damping);
	~XPhysics();

	void			Integrator();
	void			ClearForce();
	void			AddForce(XMVECTOR _newForce);
	BOOL			HasFiniteMass();

	float			GetMass();
	float			GetInverseMass()						{ return m_InverseMass;			}
	XMVECTOR		GetVelocity()							{ return m_Velocity;			}
	XMVECTOR		GetPosition()							{ return m_Position;			}
	XMVECTOR		GetContactNormal()						{ return m_ContactNormal;		}

	void			SetInverseMass(float _inverseMass)		{ m_InverseMass = _inverseMass; }
	void			SetVelocity(XMVECTOR _newValue)			{ m_Velocity = _newValue;		}
	void			SetContactNormal(XMVECTOR _newValue)	{ m_ContactNormal = _newValue;	}

	void			RefillNOS()								{ m_NOSFuel = MAX_NOS; }
	void			ApplyNOS();
	float			GetNOSFill()							{ return m_NOSFuel; }
};


#endif