#pragma once
#ifndef _AUDIO_LISTENER_H_
#define _AUDIO_LISTENER_H_
#include "../Component.h"

class Vec2;

class AudioListener :public Component
{
	//Inherited Variables
	//-Transform2D
	//-Owner
	//IsEnabled bool
	
public://Constructors Destructors
	AudioListener();
	AudioListener(Transform2D& _transform); //Default constructor
	~AudioListener();

public://Member Variables
	//Transform2D* m_transform_2d;
	float m_gain; //Master Gain


public:	//Listener Functions
	void SetPosition(Vec2 _position);
	void SetOrientation(float _angle);
	void SetVelocity(Vec2 _velocity);


public://Component functions
	virtual void Update(double fTimeDif) override;
	//For component messages
	virtual void ReceiveMsg(const Message& message) override;
	//component Activation when it is running first time.
	virtual void Activate()override;
	//Component Deactivation before it is delete.
	virtual void Deactivate()override;

	
//Getters & Setters
	//DEsarrollar getters and setters
};

#endif


