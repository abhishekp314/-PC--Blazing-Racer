#pragma once

#ifndef __PHYSICSACTOR__
#define __PHYSICSACTOR__

#include "Util/Util.h"
#include "Game/GameActors/AnimatedActor.h"
#include "Game/XPhysics.h"
#include "Game/GameActors/SimpleActor.h"


class PhysicsActor :public AnimatedActor
{
	XPhysics				*m_PhysicsObject;
	EPhysicsActorState		m_ePhysicsActorState;
	SimpleActor				*m_NOSTailActor;
public:
	PhysicsActor();

	//To make a Physics Object Immovable, set Inverse Mass to 0
	PhysicsActor(EAssetType _assetType, XMFLOAT3 _pos, XMFLOAT3 _rot, XMFLOAT3 _scale, XMFLOAT4 _color,float _height, float _width, IDirect3DTexture9 *_pTex, float _depth,
					XMVECTOR _velocity, XMVECTOR _acceleration, float m_mass, float _damping);
	~PhysicsActor(void);

	void					Init();
	void					Update();
	void					Render();
	void					Destroy();

	QUAD					GetBoundingBox();
	void					OnCollision(PhysicsActor *_otherActor);
	void					OnNoCollision();
	XPhysics*				GetPhysicsObject()									{ return m_PhysicsObject;	   }	
	EPhysicsActorState		GetPhysicsActorState()								{ return m_ePhysicsActorState; }
	void					SetPhysicsActorState(EPhysicsActorState _value)		{ m_ePhysicsActorState = _value; }
	//get bounding box
};


#endif