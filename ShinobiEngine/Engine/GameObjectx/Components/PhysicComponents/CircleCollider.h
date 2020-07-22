#pragma once
#ifndef _CIRCLE_COLLIDER_H_
#define _CIRCLE_COLLIDER_H_
#include "Collider.h"

class CircleCollider : public Collider
{
	//Inherited Variables
	//Owner
	//IsEnabled?
	//Transform2D
	//ColliderType
	//PhysicMaterial
	
private://Member variables
	float m_radius;

public://Constructor Destructor
	CircleCollider();
	CircleCollider(Transform2D& _transform, PhysixMaterial& _material, float l_radius);
	~CircleCollider();

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

	virtual bool collides(const Collider& other, Manifold& hit) const override;
	virtual bool collides(const Transform2D& circlePos, float circleRadius, Manifold& hit) const override;
	virtual bool collides(const Transform2D& rectPos, const Vec2& rectSize, Manifold& hit) const override;
	virtual bool collides(const Transform2D& pixelsPos, const Vec2& pixelSize, const uint8_t* pixels, Manifold& hit)const override;

	//Getters & Setters
	inline void setRadius(float l_rad) { m_radius = l_rad; }
	inline float getRadius()const { return m_radius; }
};

#endif


