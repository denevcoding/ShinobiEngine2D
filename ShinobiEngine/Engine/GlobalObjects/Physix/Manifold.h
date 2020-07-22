#pragma once
#ifndef _MANIFOLD_H_
#define _MANIFOLD_H_

#include "../../../Global/MathTools/Vec2.h"
#include "../../GameObjectx/Components/PhysicComponents/PhysixBody.h"

class Manifold
{
public:
    // cosntructor predeterminado
    Manifold();
    // Crear a partir de dos escalares
    Manifold(PhysixBody* objectA, PhysixBody* ObjectB);

    PhysixBody* bodie1;
    PhysixBody* bodie2;

    float e; // Mixed restitution
    float df; // Mixed dynamic friction
    float sf; // Mixed static friction

	//The collider Class Calculate this in the check Shapes
    Vec2 normal; //Normal vector to repositioning the objects in the direction of the collision
    float penetration = 0; //Amount of penetratiion in area points
	
    Vec2 contacts[2]; // Points of contact during collision
    int contacts_count; // Number of contacts that occured during collision
	

    void Solve(void); // Generate contact information
    void Initialize(void); // Precalculations for impulse solving
    void ApplyImpulse(void); // Solve impulse and apply
    void InfinityMassCorrection(void);// Naive correction of positional penetration
    void PositionalCorrection(void);
};
#endif


