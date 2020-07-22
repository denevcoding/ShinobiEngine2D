#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "../Component.h"

#include "stdafx.h"
#include "PhysixBody.h"

class Manifold;
class Vec2;
class Transform2D;


class Collider : public Component
{
	//Inherited Variables
	//Owner
	//IsEnabled?
	//Transform2D

public://Cosntructor Destructor
	Collider(){}
	virtual ~Collider(){}//Destruir punteros de phisic material

public:
	enum ColliderType
	{
		RECT_COLLIDER,
		CIRCLE_COLLIDER,
		PIXEL_COLLIDER
	};
	ColliderType colliderType; //To identify the collider type in some physix Engine funcs
	PhysixMaterial physixMaterial;
	
public: //Class functions
	virtual	void CalculateMass(MassData& _mass, PhysixBody* _rigid)const = 0;
	virtual void DrawCollider()const = 0;
	
	virtual bool collides(const Collider& other, Manifold& hit) const = 0;
	virtual bool collides(const Transform2D& circlePos, float circleRadius, Manifold& hit) const = 0;
	virtual bool collides(const Transform2D& rectPos, const Vec2& rectSize, Manifold& hit) const = 0;
	virtual bool collides(const Transform2D& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, Manifold& hit) const = 0;

	// chek circle
	bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2, Manifold& hit)const;
	bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize, Manifold& hit)const;
	bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, Manifold& hit)const;

	//Optonial comprobatons with optimizations
	//For Circles
	bool CircleCircleUnoptimized(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2, Manifold& hit) const;
	bool CircleCircleOptimized(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2, Manifold& hit) const;
	

	//check rect
	bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2, Manifold& hit)const;

	//check Pixels 
	bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2, Manifold& hit)const;
	bool checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize, Manifold& hit)const;




};
#endif

