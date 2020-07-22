#pragma once
#ifndef _PHYSIX_ENGINE_H_
#define _PHYSIX_ENGINE_H_
#include "../../Global/MathTools/Vec2.h"
#include "../GameObjectx/Components/PhysicComponents/PhysixBody.h"
#include "../GlobalObjects/Physix/Manifold.h"
#include "../../Global/TimeManager.h"


//Hay que mejorar el stepping y meter rotaciones y friccion

class PhysixEngine
{
private: // Manager Variables
	Vec2 m_gravity;
	int m_iterations;
	float m_gravityScale;
	
	std::vector<Collider*>m_ColliderObjs;// Array of Physics Components objects.
	
	std::vector<PhysixBody*>m_PhysixObjs;// Array of Physics Components objects.
	
	std::vector<Manifold>m_pairs;
	std::vector<Manifold>m_Uniquepairs;

	TimeManager m_TimeManager; //Time to control game time

	
public://Singleton Functions
	static PhysixEngine& GetInstance(); //Singleton
	PhysixEngine(PhysixEngine const&) = delete; //Delete the default constructor
	void operator = (PhysixEngine const&) = delete; // Delete the operator to avoid copy constructor


	
public://Managers Functions
		//Initialization
	void Init();
	//Update
	void PhysixUpdate();
	// Shutdown.
	void Terminate();

	void UpdateBodies(double DeltaTime);

private://Manager Private functions
	PhysixEngine();
	// Private constructor for singleton




	void GeneratePairs();
	static bool SortPairs(const Manifold& lhs, const Manifold& rhs);

	void ExplicitEuler(PhysixBody* bodie, float FixedDeltaTime);
	void SymplecticEuler(PhysixBody* bodie, float FixedDeltaTime);

	// Update rigid objects and collider objects.
	void IntegrateForces(PhysixBody* bodie, float _DeltaTime);
	void IntegrateVelocities(PhysixBody* bodie, float _DeltaTime);
	
	
	//To resolve the forces and impulses when two objects collides
	//void ResolveCollition(Manifold& hit);
	//void CalculateCollisions();
	//To calculate and position the objects when hits the screen edges
	//void BorderCollisions(Collider* l_collObject);



public:	//Getters & setters -- Insert Delete
	inline Vec2& GetGravity() { return m_gravity; }

	// Insert PhysX object.
	void InsertPhysixObj(PhysixBody& physixBodie);
	// Delete PhysX object.
	void DeletePhysixObj(PhysixBody& physixBodie);
	
	// Insert Colldier object.
	void InsertColliderObj(Collider& colliderObj);
	// Delete Colldier object.
	void DeleteColliderObj(Collider& colliderObj);
};

#endif
