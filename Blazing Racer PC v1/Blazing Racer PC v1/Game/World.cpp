#include "stdafx.h"
#include "Game/World.h"
#include "game/GameActors/PhysicsActor.h"
#include "Util/Util.h"
#include "Graphics/Camera.h"

using namespace Graphics;

World* World::ms_pWorld=nullptr;

extern Camera *g_pCamera;

World::World(void)
{
		m_InstanceID=0;
}


World::~World(void)
{
}

World* World::GetInstance()
{
	if(ms_pWorld==nullptr)
	{
		ms_pWorld=new World();
	}
	return ms_pWorld;
}

void World::Init()
{
	map<int,IActor*>::iterator it;
	for(it=m_GameObjects.begin();it!=m_GameObjects.end();it++)
	{
		it->second->Init();
	}
}

void World::Update()
{
	map<int,IActor*>::iterator it;
	for(it=m_GameObjects.begin();it!=m_GameObjects.end();it++)
	{
		it->second->Update();
	}
}

void World::Render()
{
	map<int,IActor*>::iterator it;
	for(it=m_GameObjects.begin();it!=m_GameObjects.end();it++)
	{
		float camYPos	= g_pCamera->GetCameraPosition().y;
		float actorYPoS = it->second->GetPosition().y;
		
		if(abs(camYPos - actorYPoS) < SCREEN_HEIGHT)
			it->second->Render();
	}
}

void World::AddActor(IActor *_actor)
{
	m_GameObjects[m_InstanceID]=_actor;

	if(_actor->GetActorType() == ACTORTYPE_PHYSICS)
	{	
		if(_actor->GetAssetType() == ASSETTYPE_PLAYER)
		{
			vector<int>::iterator it = m_PhysicsActorIDs.begin();
			m_PhysicsActorIDs.insert(it, m_InstanceID);
		}
		m_PhysicsActorIDs.push_back(m_InstanceID);
	}
	m_InstanceID++;
}

void World::RemoveActor(int _key)
{
	if(m_GameObjects[_key]!=nullptr)
	{
		m_GameObjects[_key]->Destroy();
		delete(m_GameObjects[_key]);

		map<int,IActor*>::iterator it;
		it=m_GameObjects.find(_key);

		m_GameObjects.erase(it);
	}
}

void World::Destroy()
{
	map<int,IActor*>::iterator it;
	for(it=m_GameObjects.begin();it!=m_GameObjects.end();it++)
	{
		it->second->~IActor();
	}
}

void World::CheckAllCollisions()
{
	PhysicsActor *obj1, *obj2;
	int id1,id2;
	QUAD q1,q2;
	map<int,IActor*>::iterator it;
	for(vector<int>::iterator i=m_PhysicsActorIDs.begin(); i!=m_PhysicsActorIDs.end()-1; i++)
	{
		for(vector<int>::iterator j=i+1; j!=m_PhysicsActorIDs.end(); j++)
		{
			id1=*i;
			id2=*j;
		
			obj1=(PhysicsActor*)m_GameObjects[id1];
			obj2=(PhysicsActor*)m_GameObjects[id2];

			if(abs(obj1->GetPosition().y - obj2->GetPosition().y) < 400)
			{

				q1=obj1->GetBoundingBox();
				q2=obj2->GetBoundingBox();

			//find collisions
			if(Intersect(q1,q2, obj1))// || Intersect(q2,q1, obj1))
			{
				obj1->OnCollision(obj2);
				//obj2->OnCollision(obj1);
				break;
			}
		/*	//Not required when u have textures applied
			else
			{	
				obj1->SetColor(XMFLOAT4(0,255,0,255));
				obj2->SetColor(XMFLOAT4(0,255,0,255));
			}*/
			}
		}
	}
}

bool World::Intersect(QUAD q1,QUAD q2, PhysicsActor *_pObj1)
{
	XMFLOAT3 topLeft1 = q1.a;
	XMFLOAT3 topLeft2 = q2.a;

	float width1  = q1.width; 
	float height1 = q1.height;
	
	float width2  = q2.width; 
	float height2 = q2.height;


	XMFLOAT3 v1, v2, v3, v4, u1, u2, u3, u4;
	XMVECTOR contactNormal = {0, 0, 0};
	BOOL	 isCollided = false;

	//Vertices of Quad 1
	v1   = topLeft1;	
	v2.x = topLeft1.x + width1;		v2.y = topLeft1.y;
	v3.x = topLeft1.x;				v3.y = topLeft1.y - height1;
	v4.x = topLeft1.x + width1;		v4.y = topLeft1.y - height1;

	//Vertices of Quad 2
	u1   = topLeft2;	
	u2.x = topLeft2.x + width2;		u2.y = topLeft2.y;
	u3.x = topLeft2.x;				u3.y = topLeft2.y - height2;
	u4.x = topLeft2.x + width2;		u4.y = topLeft2.y - height2;

	
	//v1 test in u rect
	if(v1.x >= u1.x && v1.x <= u2.x  &&  v1.y <= u1.y && v1.y >= u3.y)
	{
		//Set ContactNormal to (0.5,-0.5)
		contactNormal.x += 0.5;
		contactNormal.y += -0.5;
		isCollided = true;
	}

	//v2 test in u rect
	if(v2.x >= u1.x && v2.x <= u2.x  &&  v2.y <= u1.y && v2.y >= u3.y)
	{
		//Set ContactNormal to (-0.5,-0.5)
		contactNormal.x += -0.5;
		contactNormal.y += -0.5;
		isCollided = true;
	}

	//v3 test in u rect
	if(v3.x >= u1.x && v3.x <= u2.x  &&  v3.y <= u1.y && v3.y >= u3.y)
	{
		//Set ContactNormal to (0.5,0.5)
		contactNormal.x += 0.5;
		contactNormal.y += 0.5;
		isCollided = true;
	}


	//v4 test in u rect
	if(v4.x >= u1.x && v4.x <= u2.x  &&  v4.y <= u1.y && v4.y >= u3.y)
	{
		//Set ContactNormal to (-0.5,0.5)
		contactNormal.x += -0.5;
		contactNormal.y +=  0.5;
		isCollided = true;
	}

	if(v1.x <= u3.x && v2.x >= u4.x && v1.y >= u3.y && v1.y <= u1.y)// && v3.y <= u3.y)
	{
		//Set contact Normal to (0, -1, 0)
		contactNormal.x += 0;
		contactNormal.y += -1;
		isCollided = true;
	}
	
	if(v3.x <= u1.x && v4.x >= u2.x && v3.y <= u1.y && v3.y >= u3.y)//&& v4.y <= u2.y)
	{
		//Set contact Normal to (0, 1, 0)
		contactNormal.x += 0;
		contactNormal.y += 1;
		isCollided = true;
	}
	
	if(v1.x <= u2.x && v1.x >= u1.x && v3.x <= u4.x && v3.x >= u3.x && v1.y >= u2.y && v3.y <= u4.y)
	{
		//Set contact Normal to (1, 0, 0)
		contactNormal.x += 1;
		contactNormal.y += 0;
		isCollided = true;
	}

	
	if(v2.x >= u1.x && v2.x <=u2.x && v4.x >= u3.x && v4.x <= u4.x && v2.y >= u1.y && v4.y <= u3.y)
	{
		//Set contact Normal to (-1, 0, 0)
		contactNormal.x += -1;
		contactNormal.y +=  0;
		isCollided = true;
	}
	

	_pObj1->GetPhysicsObject()->SetContactNormal(contactNormal);

	if(isCollided)
		return true;
	else
		return false;
}

IActor* World::GetActor(int _InstanceID)
{
	return m_GameObjects[_InstanceID];
}