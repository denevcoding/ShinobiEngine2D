#include "stdafx.h"
#include "RectCollider.h"
#include "../../../Managerx/PhysixEngine.h"
#include "../Transform2D.h"
#include "../../../Managerx/GraphicsEngine.h"

RectCollider::RectCollider()
{
	colliderType = ColliderType::RECT_COLLIDER;
	m_transform_2d = nullptr;
	m_rectSize = Vec2(0, 0);
	physixMaterial = PhysixMaterial();
	m_isEnabled = false;	
}

RectCollider::RectCollider(Transform2D& _transform, PhysixMaterial& _material, Vec2 _size)
{
	colliderType = ColliderType::RECT_COLLIDER;
	Vec2 position = Vec2(_transform.m_vPos.x, _transform.m_vPos.y);
	m_transform_2d = &_transform;
	m_transform_2d->SetPos(position);

	//Dependeing on scale values of the transform
	float realSizeX = _size.GetX() * _transform.GetScale().x;
	float realSizeY = _size.GetY() * _transform.GetScale().y;	
	m_rectSize = Vec2(realSizeX, realSizeY);

	physixMaterial = _material;


	m_isEnabled = true;
	//Registering Collider Object object in graphics engine
	GraphicsEngine::GetInstance().InsertColliderObj(*this);
	PhysixEngine::GetInstance().InsertColliderObj(*this);	
}



//Component Functions
void RectCollider::Update(double fTimeDiff)
{
	
}

void RectCollider::ReceiveMsg(const Message& message)
{
}

void RectCollider::Activate()
{
	//Activating component
	m_isEnabled = true;
}

void RectCollider::Deactivate()
{
	//Disabling component
	m_isEnabled = false;
}


void RectCollider::CalculateMass(MassData& _mass, PhysixBody* _rigid) const
{
	assert(_rigid != nullptr);

	if (_rigid->m_bIsKinematic == true)
	{
		_mass.inv_mass = 0;
		_mass.inv_mass = 0;
	}
	else
	{
		float width = m_rectSize.x;
		float heigh = m_rectSize.y;

		_mass.mass = width * heigh * physixMaterial.density;
		_mass.inv_mass = 1 / _mass.mass;
	}
	//Inertia and rotate
}

void RectCollider::DrawCollider() const
{
	lgfx_setblend(BLEND_MUL);
	lgfx_setcolor(255, 0, 0, 0.5f);
	float offsetX = m_rectSize.x /2;
	float offsetY = m_rectSize.y /2;
	lgfx_drawrect(m_transform_2d->m_vPos.x - offsetX, m_transform_2d->m_vPos.y - offsetY , m_rectSize.x, m_rectSize.y);
}


bool RectCollider::collides(const Collider& other, Manifold& hit) const
{
	bool collision = other.collides(*m_transform_2d, m_rectSize, hit);
	return collision;
}

bool RectCollider::collides(const Transform2D& circlePos, float circleRadius, Manifold& hit) const
{
	return checkCircleRect(circlePos.GetPos(), circleRadius, m_transform_2d->GetPos(), m_rectSize, hit);
}

bool RectCollider::collides(const Transform2D& rectPos, const Vec2& rectSize, Manifold& hit) const
{
	return checkRectRect(rectPos.GetPos(), rectSize, m_transform_2d->GetPos(), m_rectSize, hit);
}

bool RectCollider::collides(const Transform2D& pixelsPos, const Vec2& pixelSize, const uint8_t* pixels, Manifold& hit) const
{
	return checkPixelsRect(pixelsPos.GetPos(), pixelSize, pixels, m_transform_2d->GetPos(), m_rectSize, hit);
}


RectCollider::~RectCollider()
{
	//Deregestering rendereable object in graphics engine
	PhysixEngine::GetInstance().DeleteColliderObj(*this);
}