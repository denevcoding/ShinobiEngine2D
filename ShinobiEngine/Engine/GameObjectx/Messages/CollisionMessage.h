#pragma once
#ifndef _COLLISION_MSG_H_
#define _COLLISION_MSG_H_
#include "Message.h"
class GameObject;

//Collision msg
class CollisionMessage : public Message
{
};

//GameObject collision msg
class GameObjectCollisionMsg : public CollisionMessage
{
private:
	GameObject* gObjectToCall; //GameObject to collide

public:
	GameObjectCollisionMsg(GameObject& gObject) : gObjectToCall(&gObject)
	{};

	inline const GameObject* GetObjectToCall() const { return gObjectToCall; }
};





//Limit collisionMsg
class LimitWorldCollMsg : public CollisionMessage
{
public:
	//Collision limit 
	//To use operators i.e value = LIMIT_X_NEG & LIMIT_Y_NEG indicates negative limits x and y in same value
	enum eType : __int8 {
		LIMIT_X_NEG = 1,
		LIMIT_X_POS = 2,
		LIMIT_Y_NEG = 3,
		LIMIT_Y_POS = 8
	};
private:
	__int8 m_uLimit; // Limit World

public:
	LimitWorldCollMsg(_int8 uLimit) : m_uLimit(uLimit)
	{}

	inline _int8 GetTypeLimitWorldColl()const { return m_uLimit; }
};

#endif

