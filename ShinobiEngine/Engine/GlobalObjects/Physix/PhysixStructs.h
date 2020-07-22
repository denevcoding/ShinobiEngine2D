#pragma once

#ifndef _MASS_DATA_
#define _MASS_DATA_
typedef struct MassData
{
	//Impulse Resolution
	float mass;
	float inv_mass;
	//For rotations
	float inertia;
	float inverse_invertia;
} MassData;

#endif _MASS_DATA_


//Useful Settings for common materials

//Rock       Density : 0.6  Restitution : 0.1
//Wood       Density : 0.3  Restitution : 0.2
//Metal      Density : 1.2  Restitution : 0.05
//BouncyBall Density : 0.3  Restitution : 0.8
//SuperBall  Density : 0.3  Restitution : 0.95
//Pillow     Density : 0.1  Restitution : 0.2
//Static     Density : 0.0  Restitution : 0.4
#ifndef _PHYSIX_MATERIAL_H_
#define _PHYSIX_MATERIAL_H_

typedef struct PhysixMaterial
{
	float density;
	float restitution;
	
	float staticFriction;
	float dynamicFriction;
	
	//float airFriction;
}PhysixMaterial;

#endif _PHYSIX_MATERIAL_





