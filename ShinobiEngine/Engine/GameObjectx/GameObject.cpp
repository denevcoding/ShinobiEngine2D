#include "stdafx.h"
#include "GameObject.h"
#include "Components/Transform2D.h"
#include "../../Global/EngineSettings.h"
#include "Components/Component.h"

GameObject::GameObject(void)
{
	this->m_name = "GameObject";
	this->m_tag = "";
	bool m_isEnabled = false;
	HRESULT l_result = CoCreateGuid(&m_guid);

	Vec2 defaultPosition = Vec2(GeneralSettings::WindowWidth / 2, GeneralSettings::WindowHeight / 2);
	Vec2 defaultScale = Vec2(1, 1);
	
	//Create Transform component by default
	m_transform_2d = new Transform2D(defaultPosition, defaultScale);
	this->AddComponent<Transform2D&>(*m_transform_2d);
}


//Initialization Constructor
GameObject::GameObject(std::string l_name, std::string l_tag)
{
	//Adding Unique ID
	HRESULT l_result = CoCreateGuid(&m_guid);
	this->m_name = l_name;
	this->m_tag = l_tag;
	this->m_isEnabled = true;

	//Setting up The basics
	//Half of the screen is the default Transform position 
	Vec2 defaultPosition = Vec2(GeneralSettings::WindowWidth / 2, GeneralSettings::WindowHeight / 2);
	Vec2 defaultScale = Vec2(1, 1);

	//Adding Transform Component by Default
	m_transform_2d = new Transform2D(defaultPosition, defaultScale);
	this->AddComponent<Transform2D&>(*m_transform_2d);
}


//Destructor
GameObject::~GameObject(void)
{
	for (components_vector_itr itr = m_components_list.begin(); itr != m_components_list.end(); ++itr)
	{
		delete* itr;
	}
	m_components_list.clear();
}

void GameObject::Activate()
{
	for (components_vector_itr itr = m_components_list.begin(); itr != m_components_list.end(); ++itr)
	{
		(*itr)->Activate();
	}
	this->m_isEnabled = true;
}

void GameObject::Deactivate()
{
	for (components_vector_itr itr = m_components_list.begin(); itr != m_components_list.end(); ++itr)
	{
		(*itr)->Deactivate();
	}
	this->m_isEnabled = false;
}

//Functions Related to components
void GameObject::Update(double fTimeDiff)
{
	if (this->m_isEnabled == true) //GameObject Activated
	{
		//Activate();
		for (components_vector_itr itr = m_components_list.begin(); itr != m_components_list.end(); ++itr)
		{
			if ((*itr)->GetEnabled() == true)
			{
				(*itr)->Update(fTimeDiff);
			}			
		}
	}	
}

void GameObject::SendMsg(const Message& message) const
{
	if (m_isEnabled == true)
	{
		for (auto compIt = m_components_list.begin(); compIt != m_components_list.end(); ++compIt) {
			(*compIt)->ReceiveMsg(message);
		}
	}
}