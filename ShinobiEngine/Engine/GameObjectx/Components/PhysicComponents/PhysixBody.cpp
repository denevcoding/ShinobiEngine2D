#include "stdafx.h"
#include "PhysixBody.h"
#include "../ShinobiEngine/Engine/GameObjectx/GameObject.h"
#include "../../../Managerx/PhysixEngine.h"
#include "Collider.h"

PhysixBody::PhysixBody()
	:m_shape(nullptr)
	, m_vVel(Vec2(0, 0))

	, m_forces(Vec2(0, 0))
	, m_bIsKinematic(false)
	, gravityScale(1.f)
	, m_bUseGravity(true)
{
	m_transform_2d = nullptr;
	m_mass_data = MassData();
	m_isEnabled = false;
}


PhysixBody::PhysixBody(Transform2D& _transform, Collider* _collider, bool _kinematic)
:m_shape(_collider)
,m_vVel(Vec2(0, 0))
,m_forces(Vec2(0, 0))
,m_bIsKinematic(_kinematic)
,gravityScale(1.f)
,m_bUseGravity(true) // not used yet
{

	if (m_shape != nullptr)
	{
		//This bodie has a shape so... The calculate the mass depending of the area an density and volume
		m_shape->CalculateMass(m_mass_data, this);
	}
	else
	{
		//fill mass data by default
		if (m_bIsKinematic)
		{
			SetStatic();
		}
		else
		{
			SetDefaultMass();
		}
	}
	
	m_transform_2d = &_transform;
	m_isEnabled = true;
	//Registering Collider Object object in graphics engine
	PhysixEngine::GetInstance().InsertPhysixObj(*this);
}



//Class functions
void PhysixBody::ApplyImpulse(Vec2 impulse)
{
	m_vVel += impulse * m_mass_data.inv_mass;
	//Angular Velocity
}

void PhysixBody::ApplyForce(Vec2& force)
{
	m_forces += force;
}



void PhysixBody::SetOrient()
{
}
void PhysixBody::SetDefaultMass()
{
	m_mass_data.mass = 1;
	m_mass_data.inv_mass = 1 / m_mass_data.mass;

	//Rotations
	m_mass_data.inertia = 1;
	m_mass_data.inverse_invertia = 1 / m_mass_data.inertia;
	
}
void PhysixBody::SetStatic()
{
	m_mass_data.mass = 0;
	m_mass_data.inv_mass = 0;

	//Rotations
	m_mass_data.inertia = 0;
	m_mass_data.inverse_invertia = 0;
}





//Component Funtions
void PhysixBody::Update(double fTimeDiff)
{
}

void PhysixBody::ReceiveMsg(const Message& message)
{
}

//Physics update
void PhysixBody::FixedUpdate(double fTimeDiff)
{
}

void PhysixBody::Activate()
{
	//Activating component
	m_isEnabled = true;
}

void PhysixBody::Deactivate()
{
	//Disabling component
	m_isEnabled = false;
}

//Destructor
PhysixBody::~PhysixBody()
{
	//Deregestering rendereable object in graphics engine
	PhysixEngine::GetInstance().DeletePhysixObj(*this);
}