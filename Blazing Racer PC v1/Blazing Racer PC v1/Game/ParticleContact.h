#pragma once

#ifndef __PARTICLECONTACT__
#define __PARTICLECONTACT__

#include "Game/GameActors/PhysicsActor.h"
#include "Game/XPhysics.h"


class ParticleContact
{
	static ParticleContact*		ms_pParticleContact;

	XPhysics					*m_pParticle1, *m_pParticle2;
	float						m_restitution;
	float						m_penetration;
	XMVECTOR					m_contactNormal;

	ParticleContact()
	{

	}
	
public:
	static ParticleContact*		GetInstance();
	~ParticleContact(void);

	void						ContactResolve(XPhysics *_p1, XPhysics *_p2, float _restitution, float penetration, XMVECTOR _contactNormal);
	float						CalculateSeparatingVelocity();
	void						ResolveVelocity();
	void						ResolvePenetration();
	void						ResolveDragging(XPhysics *_p1, XPhysics *_p2, float _restitution, float penetration, XMVECTOR _contactNormal);
};


#endif
