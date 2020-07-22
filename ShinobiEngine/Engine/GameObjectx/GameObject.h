#pragma once
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_
#include "Components/Transform2D.h"
#include "../ShinobiEngine/Global/EngineSettings.h"

class Component;
class Message;

class GameObject
{
public: //Functions - Constructors
	GameObject(void);
	GameObject(std::string l_name, std::string l_tag);
	~GameObject(void);
	
private:
	// We define our vectors of components and its iterators as a type to manipulate easier
	typedef std::vector<Component*> components_vector;
	typedef components_vector::iterator components_vector_itr;
	typedef components_vector::const_iterator components_vector_const_itr;
	components_vector m_components_list;

public: //Variables
	Transform2D* m_transform_2d;
	std::string m_name;        //The basic Id of the GameObject example: "Player", "Enemy"
	std::string m_tag;         //You can use this for example to agroup different objects of one type for example: "ENEMIES, ITEMS" 	
	bool m_isEnabled;          //We can have objects without being enabled this means this object wont be printed o the screen but it will exist on the game for the porpuses of an specific funcionality 
	GUID m_guid;			   // A unique Id for every GameObject

public:
	// Entity activation when it's running first time.
	void Activate(void);
	// Entity deactivation before is deleted.
	void Deactivate(void);
	// Process slot.
	void Update(double fTimeDiff);
	// Sends a message to its components.
	void SendMsg(const Message& message) const;


	// Add a component.
	template <class T>
	void AddComponent(T& component)
	{
		m_components_list.push_back(&component);
		component.SetOwner(*this);
	}

	// Find a component.
	template <class T>
	T* FindComponent() const
	{
		for (auto compIt = m_components_list.begin(); compIt != m_components_list.end(); ++compIt) {
			T* pComp = dynamic_cast<T*>(*compIt);
			if (pComp != nullptr) {
				return pComp;
			}
		}
		return nullptr;
	}	
};

#endif


