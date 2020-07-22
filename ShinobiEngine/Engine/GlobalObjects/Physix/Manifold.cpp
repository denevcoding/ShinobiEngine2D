#include "stdafx.h"
#include "Manifold.h"
#include "../../GameObjectx/GameObject.h"
#include "../../GameObjectx/Components/PhysicComponents/Collider.h"
#include "../../GameObjectx/Components/Transform2D.h"
#include "../ShinobiEngine/Engine/GlobalObjects/Physix/PhysixStructs.h"
#include "../../../Global/MathTools/utils.h"


//Consttructor Manifold
Manifold::Manifold()
    : bodie1(nullptr)
    , bodie2(nullptr)
{
}


Manifold::Manifold(PhysixBody* objectA, PhysixBody* ObjectB)
    : bodie1(objectA)
    , bodie2(ObjectB)
    , normal(Vec2(0, 0))
{
}


void Manifold::Solve()
{
    Collider* collider1 = bodie1->GetOwner()->FindComponent<Collider>();
    Collider* collider2 = bodie2->GetOwner()->FindComponent<Collider>();
	
    if (!collider1->collides(*collider2, *this))
    {
        //Theres no contact
        contacts_count = 0;
    }
    else
    {
        contacts_count = 1;
    }
}


//Class functions
void Manifold::Initialize()
{
    //Calculate Average restitution
    e = min(bodie1->m_shape->physixMaterial.restitution, bodie2->m_shape->physixMaterial.restitution);
	
    // Calculate static and dynamic friction
    sf = /*sqrtf*/(pow(bodie1->m_shape->physixMaterial.staticFriction,2) * pow(bodie2->m_shape->physixMaterial.staticFriction,2));
    df = /*sqrtf*/(pow(bodie1->m_shape->physixMaterial.dynamicFriction,2) * pow(bodie2->m_shape->physixMaterial.dynamicFriction,2));
}


void Manifold::ApplyImpulse(void)
{
	const float bodie1_InvMass = bodie1->m_mass_data.inv_mass;
	const float bodie2_InvMass = bodie2->m_mass_data.inv_mass;

	if (Utils::Equal(bodie1_InvMass + bodie2_InvMass,0))
	{
		InfinityMassCorrection();
		return;
	}

	for (uint32_t i = 0; i < contacts_count; ++i)
	{
		//Calculate Relative Velocity
		Vec2 rv = bodie2->GetVel() - bodie1->GetVel();

		//I think the equation of the dot product(equation 3) is wrong shouldnt it be x1* x2 + y1 * y2 instead of x1 * x2 + y2 * y2 ?

		//Equation 8 should be : V'A = VA - (j*n)/massA, and V'B = VB + (j * n) / massB, as written in the code example instead of the other way around.

		//	Using this change, equation 8 + 5 would be :
		//(VB + (j * n) / massB - VA + (j * n) / massA) dot n = -e * (VB - VA) dot n
		//	which when simplified accordingly will now correctly give the derived equation :
		//j = -(1 + e)((VB - VA) dot n) / (1 / massB + 1 / massA),
		//	note that during simplification, n dot n equals 1.
		
		// Calculate relative velocity in terms of the normal direction
		float velAlongNormal = Vec2::dot(rv, normal);
		//float velAlongNormal = rv.dot(rv, normal);

		// Do not resolve if velocities are separating
		if (velAlongNormal > 0)
			return;

		//Calculate impulsar escalar		
		float j = (-(1 + e) * velAlongNormal) / (bodie1_InvMass + bodie2_InvMass);
		//j /= contacts_count;		
		
		//Apply impulse
		Vec2 impulse =  normal * j;
		
		bodie1->ApplyImpulse(-impulse);
		bodie2->ApplyImpulse(impulse);

		

		////Friction Impulse::::::::::::::::::::::::::::::::
		////Calculate Relative Velocity
		rv = bodie2->GetVel() - bodie1->GetVel();

		//Solve for magnitude to apply along the friction vector		
		//Vec2 tangent = rv - normal * (-Vec2::dot(rv, normal));
		//tangent.Normalize();

		Vec2 tangent;
		if(Vec2::Cross(rv, normal)<0)
		{			
			tangent = Vec2(-normal.y, normal.x);
		}
		else
		{
			tangent = Vec2(normal.y, -normal.x);			
		}
		

		//j Tangent magnitude
		float jt = -Vec2::dot(rv, tangent);
		jt /= bodie1_InvMass + bodie2_InvMass;

		//Dont apply tiny friction impulses
		if (Utils::Equal(jt,0.0f))
		    return;

		//Columbs Law
		// PythagoreanSolve = A^2 + B^2 = C^2, solving for C given A and B
		// Use to approximate mu given friction coefficients of each body
		//float mu = Utils::PythagoreanSolve(bodie1->m_shape->physixMaterial.staticFriction, bodie2->m_shape->physixMaterial.staticFriction);

		// Clamp magnitude of friction and create impulse vector
		Vec2 frictionImpulse;
		if (abs(jt) < j * sf)
		{
			frictionImpulse = tangent * jt;
		}
		else
		{
			frictionImpulse =  tangent * -j * df;
		}
		
		//Apply
		//bodie1->m_vVel -= frictionImpulse * bodie1_InvMass;
		//bodie2->m_vVel += frictionImpulse * bodie2_InvMass;
		bodie1->ApplyImpulse(-frictionImpulse);
		bodie2->ApplyImpulse(frictionImpulse);
	}
}

void Manifold::PositionalCorrection()
{
	//Positional Correction
	const float  k_slop = 0.01f; // Penetration allowance
	const float percent = 0.2f;  // Penetration percentage to correct
	Vec2 correction = (normal * percent) * (max(penetration - k_slop, 0.0f) / (bodie1->m_mass_data.inv_mass + bodie2->m_mass_data.inv_mass));

	bodie1->m_transform_2d->m_vPos -= correction * bodie1->m_mass_data.inv_mass;
	bodie2->m_transform_2d->m_vPos += correction * bodie2->m_mass_data.inv_mass;
}


void Manifold::InfinityMassCorrection() //Revisar esto con la documentacion online
{
	bodie1->m_vVel = Vec2(0, 0);
	bodie2->m_vVel = Vec2(0, 0);
}
