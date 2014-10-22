#include "stdafx.h"
#include "Game/ParticleContact.h"


ParticleContact* ParticleContact::ms_pParticleContact = nullptr;

ParticleContact::~ParticleContact(void)
{
}

ParticleContact* ParticleContact::GetInstance()
{
	if(ms_pParticleContact == nullptr)
		ms_pParticleContact = new ParticleContact();
	return ms_pParticleContact;
}

void ParticleContact::ContactResolve(XPhysics *_p1, XPhysics *_p2, float _restitution, float penetration, XMVECTOR _contactNormal)
{
	this->m_pParticle1		=	_p1;
	this->m_pParticle2		=	_p2;
	this->m_restitution		=	_restitution;
	this->m_contactNormal	=	_contactNormal;

	ResolveVelocity();
	ResolvePenetration();
}

float ParticleContact::CalculateSeparatingVelocity()
{
	XMVECTOR relativeVelocity =	m_pParticle1->GetVelocity();
	return XMVector3Dot(relativeVelocity, m_contactNormal).y;
}

void ParticleContact::ResolveVelocity()
{
	float separatingVelocity = CalculateSeparatingVelocity();

	if(separatingVelocity > 0)
	{
		return;
	}

	float newSeparatingVelocity = -separatingVelocity * m_restitution;

	float deltaVelocity = newSeparatingVelocity - separatingVelocity;

	float totalInverseMass = m_pParticle1->GetInverseMass();

	if(m_pParticle2 != nullptr)
		totalInverseMass += m_pParticle2->GetInverseMass();

	if(totalInverseMass<=0)
		return;

	float impulse = deltaVelocity / totalInverseMass;

	XMVECTOR impulsePerIMass = m_contactNormal * impulse;

	XMVECTOR particle1Velocity = m_pParticle1->GetVelocity();

	XMVECTOR particle2Velocity;
	if(m_pParticle2 != nullptr)
		particle2Velocity = m_pParticle2->GetVelocity();

	particle1Velocity += impulsePerIMass * m_pParticle1->GetInverseMass();
	m_pParticle1->SetVelocity(particle1Velocity);
	
	if(m_pParticle2 != nullptr)
	{
		particle2Velocity += impulsePerIMass * -m_pParticle2->GetInverseMass();
		m_pParticle2->SetVelocity(particle2Velocity);
	}
}

void ParticleContact::ResolvePenetration()
{
	//No penetation required as of now

	if(m_penetration <= 0)
		return;
}

void ParticleContact::ResolveDragging(XPhysics *_p1, XPhysics *_p2, float _restitution, float penetration, XMVECTOR _contactNormal)
{
	this->m_pParticle1		=	_p1;
	this->m_pParticle2		=	_p2;
	this->m_restitution		=	_restitution;
	this->m_contactNormal	=	_contactNormal;

	_p1->ClearForce();
	_p1->AddForce(_contactNormal * _restitution);
}
