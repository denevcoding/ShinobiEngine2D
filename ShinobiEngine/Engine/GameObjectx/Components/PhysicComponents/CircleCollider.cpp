#include "stdafx.h"
#include "CircleCollider.h"
#include "../../../Managerx/PhysixEngine.h"
#include "../Transform2D.h"
#include "../../GameObject.h"
#include "../../../../Global/EngineSettings.h"
#include "../../../Managerx/GraphicsEngine.h"

CircleCollider::CircleCollider()
{
	colliderType = ColliderType::CIRCLE_COLLIDER;
	m_transform_2d = nullptr;
	m_radius = 0.f;

	physixMaterial = PhysixMaterial();	
	m_isEnabled = false;
}

CircleCollider::CircleCollider(Transform2D& _transform, PhysixMaterial& _material, float l_radius)
{
	colliderType = ColliderType::CIRCLE_COLLIDER;
	m_transform_2d = &_transform;
	m_radius = _transform.GetScale().x * l_radius;
	
	physixMaterial = _material;	

	m_isEnabled = true;
	//Registering Collider Object object in graphics engine
	GraphicsEngine::GetInstance().InsertColliderObj(*this);
	PhysixEngine::GetInstance().InsertColliderObj(*this);	
}




//Component Functions
void CircleCollider::Update(double fTimeDiff)
{

}

void CircleCollider::ReceiveMsg(const Message& message)
{

}


void CircleCollider::Activate()
{
	//Activating component
	m_isEnabled = true;
}

void CircleCollider::Deactivate()
{
	//Disabling component
	m_isEnabled = false;
}


void CircleCollider::CalculateMass(MassData& _mass, PhysixBody* _rigid) const
{
	assert(_rigid != nullptr);

	if (_rigid->m_bIsKinematic == true)
	{
		_mass.mass = 0;
		_mass.inv_mass = 0;
	}
	else
	{
		_mass.mass = PhysicxSettings::PI * m_radius * m_radius * physixMaterial.density;
		_mass.inv_mass = 1 / _mass.mass;
	}
	//Inertia and rotate
}

void CircleCollider::DrawCollider() const
{
	lgfx_setblend(BLEND_MUL);
	float offset = (m_radius + m_radius) / 2;
	lgfx_setcolor(0, 255, 0, 0.5f);
	lgfx_drawoval(m_transform_2d->GetPos().x- offset, m_transform_2d->GetPos().y - offset, m_radius + m_radius, m_radius+ m_radius);
}


//Collides Functions
bool CircleCollider::collides(const Collider& other, Manifold& hit) const
{
	//CircleCollider* bodie1 = (CircleCollider*)hit.bodie1->m_shape;
	//bool collision = other.collides(*bodie1->m_transform_2d, bodie1->getRadius(), hit);
	
	bool collision = other.collides(*m_transform_2d, m_radius, hit);
	return collision;
}

bool CircleCollider::collides(const Transform2D& circlePos, float circleRadius, Manifold& hit) const
{
	return checkCircleCircle(circlePos.GetPos(), circleRadius, this->GetOwner()->FindComponent<Transform2D>()->GetPos(), m_radius, hit);
}

bool CircleCollider::collides(const Transform2D& rectPos, const Vec2& rectSize, Manifold& hit) const
{
	return checkCircleRect(m_transform_2d->GetPos(), m_radius, rectPos.GetPos(), rectSize, hit);
}

bool CircleCollider::collides(const Transform2D& pixelsPos, const Vec2& pixelSize, const uint8_t* pixels, Manifold& hit) const
{
	return checkCirclePixels(m_transform_2d->GetPos(), m_radius, pixelsPos.GetPos(), pixelSize, pixels, hit);
}






CircleCollider::~CircleCollider()
{
	//Deregestering rendereable object in graphics engine
	PhysixEngine::GetInstance().DeleteColliderObj(*this);
}