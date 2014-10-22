#pragma once

#ifndef __WORLD__
#define __WORLD__

#include<vector>
#include<map>
#include "Game/GameActors/IActor.h"
#include "Game/GameActors/PhysicsActor.h"

using namespace GameState;
using namespace std;

class World
{
	static World *ms_pWorld;

	int m_InstanceID;
	map<int,IActor*> m_GameObjects;
	vector<int> m_PhysicsActorIDs;

	World();
public:
	~World(void);
	static World*	GetInstance();
	void			Init();
	void			Update();
	void			Render();
	void			Destroy();

	void			AddActor(IActor *_actor);
	void			RemoveActor(int _key);
	void			CheckAllCollisions();
	bool			Intersect(QUAD _q1, QUAD _q2, PhysicsActor *_pObj1);
	IActor*			GetActor(int _instanceId);
	int				GetNumOfActors()										{ return m_InstanceID;}
};

#endif
