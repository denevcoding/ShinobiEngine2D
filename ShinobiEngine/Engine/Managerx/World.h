#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include "../../Global/TimeManager.h"

class GameObject;
class Background;
class Text;

/*World Manager Singleton*/
class World
{
public:
	//Entitie Vector - List
	typedef std::vector<GameObject*> gameObjects;
	
private://Private constructor for singleton
	World();
	void UpdateObjects(double DeltaTime);

	static const size_t MaxEntities = 10; //Max num balls

	gameObjects m_GameObjects; //Vector of gameObjects
	Background* m_Background; //Background image
	TimeManager m_TimeManager; //Time to control game time

	
public://singleton instance
	static World& GetInstance();
	World(World const&) = delete;
	void operator = (World const&) = delete;


public:	//Manager lifecycle
	void Init();
	void Terminate();
	void Update();
	
	inline TimeManager GetTimeManager() { return m_TimeManager; };
};

#endif


