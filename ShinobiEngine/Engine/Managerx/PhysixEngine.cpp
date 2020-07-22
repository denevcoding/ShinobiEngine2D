#include "stdafx.h"
#include "PhysixEngine.h"
#include "../../Global/EngineSettings.h"
#include "../GameObjectx/Components/Transform2D.h"
#include "../GameObjectx/GameObject.h"
#include "../GlobalObjects/Physix/Manifold.h"
#include "../ShinobiEngine/Engine/GameObjectx/Components/PhysicComponents/Collider.h"
#include "World.h"
#include "../GameObjectx/Components/PhysicComponents/CircleCollider.h"
#include "../GameObjectx/Messages/CollisionMessage.h"
#include "../GameObjectx/Components/PhysicComponents/RectCollider.h"
#include "../GameObjectx/Components/PhysicComponents/PhysixBody.h"


#ifndef _PAIR_H_
#define _PAIR_H_


typedef struct Pair
{
	PhysixBody* bodie1;
	PhysixBody* bodie2;

}Pair;

#endif _PAIR_H_


//For layering
#define GROUND  0x00000001 // Ground LayerMask
#define PLAYER  0x00000002 // Player LayerMask


enum eLayer : uint32_t {
	LIMIT_X_NEG = 1,
	LIMIT_X_POS = 2,
	LIMIT_Y_NEG = 4,
	LIMIT_Y_POS = 8
};


// Acceleration
//    F = mA
// => A = F * 1/m

// Explicit Euler
// x += v * dt
// v += (1/m * F) * dt


// Semi-Implicit (Symplectic) Euler
// v += (1/m * F) * dt
// x += v * dt
//
// // see http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html


// Equation4: Generalform: ax+by+c=0
//Normal to line:[ab]

PhysixEngine& PhysixEngine::GetInstance()
 
{
	// TODO: insert return statement here
	static PhysixEngine engine;
	return engine;
}

PhysixEngine::PhysixEngine()
	: m_TimeManager(PhysicxSettings::PhysicsDeltaTime)
{
	
}



//Initialize Engine
void PhysixEngine::Init()
{
	//Initialice variables
	float gravityX = PhysicxSettings::GravityX;
	float gravityY = PhysicxSettings::GravityY; // +50.f
	m_gravity = Vec2(gravityX, gravityY);
	
	m_gravityScale = PhysicxSettings::gravityScale;
	
	m_iterations = PhysicxSettings:: iIterations;

	//Clear pairs Vector
	m_pairs.clear();
	m_Uniquepairs.clear();
	
	//Clear vectors (Lists)
	m_ColliderObjs.clear();
	m_PhysixObjs.clear();
}


//--------------------------------Main Loop physics
void PhysixEngine::PhysixUpdate()
{
	//Calls Timer to process logic slot
	//m_TimeManager.InitSlotsToProcess();
	//while (m_TimeManager.ProcessSlots())
	//{
		UpdateBodies(World::GetInstance().GetTimeManager().GetFixedTick());
	//}
}
//--------------------------------Main Loop physics


void PhysixEngine::UpdateBodies(double DeltaTime)
{
	//Generate Collition Info
	GeneratePairs();
	
	//Integrate Forces to Velocity
	for (PhysixBody* pPhysixObj : m_PhysixObjs)
	{
		//Validate if the component is Enabled;
		if (!pPhysixObj->m_isEnabled)
			continue;

		//Not kinematic Object
		if (pPhysixObj->m_mass_data.inv_mass == 0.f)
			continue;

		IntegrateForces(pPhysixObj, DeltaTime);
		
	}
	

	//Initialize Collitions
	for (uint32_t i = 0; i < m_pairs.size(); ++i)
	{
		m_pairs[i].Initialize();
	}

	//Solve Collitions
	for (uint32_t j = 0; j < m_iterations; ++j)
	{
		for (uint32_t i = 0; i < m_pairs.size(); ++i)
		{
			m_pairs[i].ApplyImpulse();
		}
	}

	//Integrate Velocities toTransform
	for (PhysixBody* pPhysixObj : m_PhysixObjs)
	{
		//Validate if the component is Enabled;
		if (!pPhysixObj->m_isEnabled)
			continue;

		//Not kinematic Object
		if (pPhysixObj->m_mass_data.inv_mass == 0.f)
			continue;

		IntegrateVelocities(pPhysixObj, DeltaTime);
	}

	
	//Correct Positions
	for (uint32_t i = 0; i < m_pairs.size(); ++i)
	{
		m_pairs[i].PositionalCorrection();
	}

	
	//Clear all forces
	for (PhysixBody* PhyxBodie : m_PhysixObjs)
	{
		PhyxBodie->m_forces = Vec2(0, 0);
	}
}


void PhysixEngine::GeneratePairs()
{
	// Generates the pair list.
	// All previous pairs are cleared when this function is called.	
	m_pairs.clear();
	m_Uniquepairs.clear();

		
	for (PhysixBody* PhyxBodie : m_PhysixObjs)
	{
		for (PhysixBody* PhyxBodie2 : m_PhysixObjs)
		{
			PhysixBody* pBodieA = PhyxBodie;
			PhysixBody* pBodieB = PhyxBodie2;

			// Skip check with self
			if (pBodieA->GetOwner()->m_guid == pBodieB->GetOwner()->m_guid)
				continue;

			////This will change when the system review objects with out rigid bodie against only collider objects
			////Skip if one of them does not have collider shape associated 
			//if (pBodieA->m_shape == nullptr || pBodieB->m_shape == nullptr)
			//	continue;
			
			//Comprobate both of the bodies are not kinematic
			if (!pBodieA->m_isEnabled || !pBodieB->m_isEnabled)
				continue;

		    // Only matching layers will be considered // LAYEERING with bitmask
			/*if (!(A->layers & B->layers))
			continue;*/

			//Empty Manifold to be filled by the collision function
			Manifold hit = Manifold(pBodieA, pBodieB);
			hit.Solve();

			if (hit.contacts_count != 0)
			{
				m_pairs.emplace_back(hit);
				//m_pairs.push_back(hit);
			}
		}		
	}

	//Sorting Pairs
	std::sort(m_pairs.begin(), m_pairs.end(), &SortPairs);
	
	// Queue manifolds for solving
	{
		int i = 0;
		while (i < m_pairs.size())
		{
			Manifold manifold = *(m_pairs.begin() + i);
			m_Uniquepairs.push_back(manifold);
			++i;

			// Skip duplicate pairs by iterating i until we find a unique pair
			while (i < m_pairs.size())
			{
				Manifold potential_dup = *(m_pairs.begin() + i);
				if (manifold.bodie1 != potential_dup.bodie2 || manifold.bodie2 != potential_dup.bodie1)
					break;
				++i;
			}
		}
	}	
}
bool PhysixEngine::SortPairs(const Manifold& lhs, const Manifold& rhs)
{
	if (lhs.bodie1 < rhs.bodie1)
		return true;

	if (lhs.bodie1 == rhs.bodie1)
		return lhs.bodie2 < rhs.bodie2;

	return false;
}


void PhysixEngine::IntegrateForces(PhysixBody* bodie, float _DeltaTime)
{
	Vec2 forces = bodie->m_forces;
	
	//Integrate Forces to velocity Vector
	if (bodie->m_bUseGravity)
	{
		bodie->m_vVel += (bodie->m_forces * bodie->m_mass_data.inv_mass + (m_gravity * bodie->gravityScale))  * _DeltaTime;
	}
	else
	{
		bodie->m_vVel += (bodie->m_forces * bodie->m_mass_data.mass) * _DeltaTime;
	}

	
}
void PhysixEngine::IntegrateVelocities(PhysixBody* bodie, float _DeltaTime)
{
	bodie->m_transform_2d->m_vPos += bodie->m_vVel * _DeltaTime;
	if (fabs(bodie->m_vVel.x * bodie->m_vVel.x + bodie->m_vVel.y * bodie->m_vVel.y) < PhysicxSettings::EPSILON)
	{
		bodie->m_vVel.x = 0;
		bodie->m_vVel.y = 0;
		return;
	}
	IntegrateForces(bodie, _DeltaTime);
	
}


/*Not used yet*/
void PhysixEngine::ExplicitEuler(PhysixBody* bodie, float FixedDeltaTime)
{
	Vec2 position = bodie->m_transform_2d->GetPos();
	Vec2 velocity = bodie->GetVel();
	Vec2 forces = bodie->m_forces;

	position += velocity * World::GetInstance().GetTimeManager().GetFixedTick();
	bodie->GetTransform()->SetPos(position);

	if (bodie->m_bUseGravity)
	{
		velocity += ((forces * bodie->m_mass_data.inv_mass + (m_gravity * bodie->gravityScale))) * FixedDeltaTime;
	}
	else
	{
		velocity += (forces * bodie->m_mass_data.inv_mass) * FixedDeltaTime;
	}
	bodie->SetVel(velocity);
}
void PhysixEngine::SymplecticEuler(PhysixBody* bodie, float FixedDeltatime)
{
	Vec2 position = bodie->m_transform_2d->GetPos();
	Vec2 velocity = bodie->GetVel();
	Vec2 forces = bodie->m_forces;


	//Integrate velocities
	if (bodie->m_bUseGravity)
	{
		velocity += ((bodie->m_forces * bodie->m_mass_data.inv_mass + (m_gravity * bodie->gravityScale))) * FixedDeltatime;
	}
	else
	{
		velocity += (forces * bodie->m_mass_data.inv_mass) * FixedDeltatime;
	}

	bodie->SetVel(velocity);

	position += velocity * FixedDeltatime;
	bodie->GetTransform()->SetPos(position);
}




//Registering Rigid Bodies PhysXObjects
void PhysixEngine::InsertPhysixObj(PhysixBody& physXObject)
{
	// Control if prev. inserted.
	for (const PhysixBody* pPhysixObj : m_PhysixObjs) {
		if (pPhysixObj == &physXObject) {
			return;
		}
	}
	m_PhysixObjs.push_back(&physXObject);
}

//Desregistering PhysxObjects
void PhysixEngine::DeletePhysixObj(PhysixBody& physXObject)
{
	for (auto it = m_PhysixObjs.begin(); it != m_PhysixObjs.end(); ++it) {
		if (*it == &physXObject) {
			m_PhysixObjs.erase(it);
			break;
		}
	}
}

//Registering collider Objects Bodies PhysXObjects
void PhysixEngine::InsertColliderObj(Collider& colliderObj)
{
	// Control if prev. inserted.
	for (const Collider* pColliderObj : m_ColliderObjs) {
		if (pColliderObj == &colliderObj) {
			return;
		}
	}
	m_ColliderObjs.push_back(&colliderObj);
}

void PhysixEngine::DeleteColliderObj(Collider& colliderObj)
{
	for (auto it = m_ColliderObjs.begin(); it != m_ColliderObjs.end(); ++it) {
		if (*it == &colliderObj) {
			m_ColliderObjs.erase(it);
			break;
		}
	}
}


//Finish the Engine
void PhysixEngine::Terminate()
{
	//Clear the vectors and unregistering the objects
	m_ColliderObjs.clear();
	m_PhysixObjs.clear();
}





