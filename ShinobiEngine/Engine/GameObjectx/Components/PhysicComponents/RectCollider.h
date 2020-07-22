#pragma once
#ifndef _RECT_COLLIDER_H_
#define _RECT_COLLIDER_H_
#include "Collider.h"

class RectCollider : public Collider
{
	//Inherited Variables
	//Owner
	//IsEnabled?
	//Transform2D
	//ColliderType
	//PhysicMaterial
		
private://Member Variables
	Vec2 m_rectSize;
	
public://Cosntructor Destructor
	RectCollider();
	RectCollider(Transform2D& _transform, PhysixMaterial& _material, Vec2 _size);
	~RectCollider();

public://Component Functions	
	virtual void Update(double fTimeDiff)override;
	//component Activation when it is running first time.
	virtual void Activate()override;
	//Component Deactivation before it is delete.
	virtual void Deactivate()override;
	virtual void ReceiveMsg(const Message& message) override;

public://Collider Functions
	virtual void CalculateMass(MassData& _mass, PhysixBody* _rigid) const override;
	virtual void DrawCollider() const override;

	//collides class functions
	virtual bool collides(const Collider& other, Manifold& hit) const override;
	virtual bool collides(const Transform2D& circlePos, float circleRadius, Manifold& hit) const override;
	virtual bool collides(const Transform2D& rectPos, const Vec2& rectSize, Manifold& hit) const override;
	virtual bool collides(const Transform2D& pixelsPos, const Vec2& pixelSize, const uint8_t* pixels, Manifold& hit)const override;

public://Getters & Setters
	inline void setSize(Vec2 l_size) { m_rectSize = l_size; }
	inline Vec2 getSize()const { return m_rectSize; }	
};

#endif

