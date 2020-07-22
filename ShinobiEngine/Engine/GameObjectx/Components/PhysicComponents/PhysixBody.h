#pragma once
#ifndef _PHYSIC_BODY_H_
#define _PHYSIC_BODY_H_
#include "../Component.h"
#include "../../../GlobalObjects/Physix/PhysixStructs.h"
#include "../../../../Global/MathTools/Vec2.h"

class Collider;


class PhysixBody: public Component
{
	//Inherited Variables
	  //-Transform2D
	  //-Owner
	  //IsEnabled bool
	  

public://Constructor Destructor
	PhysixBody();
	PhysixBody(Transform2D& _transform, Collider* _collider, bool _kinematic);
	~PhysixBody();

	
public://Member Variable
	Collider* m_shape;	
	MassData m_mass_data;

	//Position by component transform
	Vec2 m_vVel;// Velocity.
	Vec2 m_forces;//Accum Forces in a moment

	//For rotations
	float angularVelocity;
	float torque;
	float orient; // radians
	
	//Other rigid bodie settings
	bool m_bIsKinematic; //To Declare Objects with inifnity mass
	float gravityScale; //Local interpretation for each object	
	bool m_bUseGravity; //If the gravity affects

	

	
public://Class Functions
	//Functions to add forces to the actual 
	void ApplyImpulse(Vec2 impulse);
	void ApplyForce(Vec2& force);

	void SetOrient();
	void SetDefaultMass();
	void SetStatic();
	
public://Component Functions
	virtual void Update(double fTimeDiff)override;
	//component Activation when it is running first time.
	virtual void Activate()override;
	//Component Deactivation before it is delete.
	virtual void Deactivate()override;
	virtual void ReceiveMsg(const Message& message) override;


	virtual void FixedUpdate(double fTimeDiff);

	
public://Getters && Setters
	inline const Vec2& GetVel() const { return m_vVel; }
	inline void SetVel(const Vec2& vVel) { m_vVel = vVel; }


	//Inline Getters and setters
	inline const MassData& GetMass() const { return m_mass_data; }
	inline void SetMass(const MassData& fMass) { m_mass_data = fMass; }
	
	  
};
#endif



