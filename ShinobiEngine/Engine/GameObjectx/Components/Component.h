#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_


class GameObject;
class Message;
class Transform2D;

class Component
{
public:
	Component() :m_objectOwner(nullptr), m_isEnabled(true) {}

public:
	GameObject* m_objectOwner; //GameObject Owner of this component
	bool m_isEnabled; //to validate if component is enabled
	Transform2D* m_transform_2d;//Default transform for all components


	inline void SetOwner(GameObject& object) { m_objectOwner = &object; }
	inline GameObject* GetOwner() const { return m_objectOwner; }

	inline void SetTransform(Transform2D& _transform) { m_transform_2d = &_transform; }
	inline Transform2D* GetTransform() const { return m_transform_2d; }
	
	inline bool GetEnabled()const { return m_isEnabled; }

	//component Activation when it is running first time.
	virtual void Activate() {}
	//Component Deactivation before it is delete.
	virtual void Deactivate() {}

	//Update Logico
	virtual void Update(double fTimeDiff) = 0;

	//Receive message from another Component
	virtual void ReceiveMsg(const Message& message) {};
};

#endif
