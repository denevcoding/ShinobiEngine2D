#include "stdafx.h"
#include "Collider.h"
#include "../../../GlobalObjects/Physix/Manifold.h"
#include "../Transform2D.h"
#include "../../../../Global/MathTools/utils.h"

#include "CircleCollider.h"
#include "RectCollider.h"


//Circle vs Circle with Manifold hit Collition
bool Collider::checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2, Manifold& hit) const
{

	Vec2 posinit = pos1;
	Vec2 n = pos2 - pos1; //To perform actual lenght
	
	float centerDistance = Vec2::get_squared_dist(pos2, posinit);

	float radiussum = radius1 + radius2;

	//Early Acces
	if (centerDistance > radiussum)
	{
		hit.contacts_count = 0;
		return false;
	}

	hit.contacts_count = 1; //There is a collision and we add
	
	//There is a collition now Compute The Manifold Hit
	float d = n.Lenght();
	
    // If distance between circles is not zero
    if (d != 0)
    {
        // Distance is difference between radius and distance
        hit.penetration = radiussum - d;

		float nx = (pos2.x - pos1.x) / centerDistance;
		float ny = (pos2.y - pos1.y) / centerDistance;
		hit.normal = Vec2(nx, ny);
    	
		hit.contacts[0] = hit.normal * radius1 + pos1;		
    }
    // Circles are on same position
	else
	{
		// Choose random (but consistent) values
		hit.penetration = radius1;
		hit.normal = Vec2(1, 0);
	}


	return true;	
}

//Rect vs Circle with Manifold hit Collition
bool Collider::checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize, Manifold& hit) const
{
	Vec2 rectPos2 = Vec2(0, 0);
	Vec2 rectSize2 = Vec2(0, 0);

	Vec2 circlePos2 = Vec2(0,0);
	float circleRadius2 = 0;

	
	if (hit.bodie1->m_shape->colliderType == ColliderType::CIRCLE_COLLIDER && hit.bodie2->m_shape->colliderType == ColliderType::RECT_COLLIDER)
	{
		//Setting circle Bodie Variables
		CircleCollider* circle_collider = static_cast<CircleCollider*>(hit.bodie1->m_shape);
		circlePos2 = circle_collider->m_transform_2d->GetPos();
		circleRadius2 = circle_collider->getRadius();
		
		//Setting Rect Variables
		RectCollider* rect_collider = static_cast<RectCollider*>(hit.bodie2->m_shape);
		rectPos2 = rect_collider->m_transform_2d->GetPos();
		rectSize2 = rect_collider->getSize();

		float XMin = rectPos2.GetX() - (rectSize2.GetX() / 2);
		float XMax = rectPos2.GetX() + (rectSize2.GetX() / 2);

		float YMin = rectPos2.GetY() - (rectSize2.GetY() / 2);
		float YMax = rectPos2.GetY() + (rectSize2.GetY() / 2);


		/*//****************/
		float closestX = Utils::clamp(circlePos2.x, XMin, XMax);
		float closestY = Utils::clamp(circlePos2.y, YMin, YMax);
		Vec2 closestpoint = Vec2(closestX, closestY);

		float distanceBetween = Vec2::get_squared_dist(circlePos2, closestpoint);


		if (distanceBetween > circleRadius2)
		{
			return false;
		}


		Vec2 n;
		n = circlePos2 - closestpoint; //Direction of the closese point
		n.Normalize();

		float penetration = circleRadius2 - distanceBetween;

		hit.contacts_count = 1;
		//hit.penetration = penetration;
		hit.normal = -n;
		//hit.contacts[0] = hit.normal * circleRadius + circlePos;

		return true;
	}


	if (hit.bodie1->m_shape->colliderType == ColliderType::RECT_COLLIDER && hit.bodie2->m_shape->colliderType == ColliderType::CIRCLE_COLLIDER)
	{
		//Setting Rect Variables
		RectCollider* rect_collider = static_cast<RectCollider*>(hit.bodie1->m_shape);
		rectPos2 = rect_collider->m_transform_2d->GetPos();
		rectSize2 = rect_collider->getSize();
		
		CircleCollider* circle_collider = static_cast<CircleCollider*>(hit.bodie2->m_shape);
		circlePos2 = circle_collider->m_transform_2d->GetPos();
		circleRadius2 = circle_collider->getRadius();

		float XMin = rectPos2.GetX() - (rectSize2.GetX() / 2);
		float XMax = rectPos2.GetX() + (rectSize2.GetX() / 2);

		float YMin = rectPos2.GetY() - (rectSize2.GetY() / 2);
		float YMax = rectPos2.GetY() + (rectSize2.GetY() / 2);


		/*//****************/
		float closestX = Utils::clamp(circlePos2.x, XMin, XMax);
		float closestY = Utils::clamp(circlePos2.y, YMin, YMax);
		Vec2 closestpoint = Vec2(closestX, closestY);

		float distanceBetween = Vec2::get_squared_dist(circlePos2, closestpoint);


		if (distanceBetween > circleRadius2)
		{
			return false;
		}

		

		Vec2 n;
		n = circlePos2 - closestpoint; //Direction of the closese point
		n.Normalize();
		
		float penetration = circleRadius2 - distanceBetween;
		
		hit.contacts_count = 1;
		//hit.penetration = penetration;
		hit.normal = n;
		//hit.contacts[0] = hit.normal * circleRadius + circlePos;

		return true;		
	}
}

//Cuadrado Cuadrado
bool Collider::checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2, Manifold& hit) const
{
	//Struct to Handle First Object 
	struct AABB_1
	{
		Vec2 min = Vec2(0, 0);
		Vec2 max = Vec2(0, 0);
	};

	//Second Object
	struct AABB_2
	{
		Vec2 min = Vec2(0, 0);
		Vec2 max = Vec2(0, 0);
	};

	hit.contacts_count = 0;

	//Extents and half extents of each object
	float topLeftX = rectPos1.GetX() - rectSize1.x / 2;
	float bottomRightX(rectPos1.GetX() + rectSize1.x / 2);

	//Point 2
	float topLeftY = rectPos1.GetY() - rectSize1.y / 2;
	float bottomRightY(rectPos1.GetY() + rectSize1.y / 2);

	AABB_1 square_1;
	square_1.min = Vec2(topLeftX, topLeftY);
	square_1.max = Vec2(bottomRightX, bottomRightY);


	//Point 1
	float topLeftX2(rectPos2.GetX() - rectSize2.GetX() / 2);
	float topLeftY2(rectPos2.GetY() - rectSize2.GetY() / 2);
	//Point2
	float bottomRightX2(rectPos2.GetX() + rectSize2.GetX() / 2);
	float bottomRightY2(rectPos2.GetY() + rectSize2.GetY() / 2);

	AABB_2 square_2;
	square_2.min = Vec2(topLeftX2, topLeftY2);
	square_2.max = Vec2(bottomRightX2, bottomRightY2);



	//With Excluiyent Operations -- Better
//-Exit with no intersection if found separated along an axis
	if (square_1.max.x < square_2.min.x || square_1.min.x > square_2.max.x)return false;
	if (square_1.max.y < square_2.min.y || square_1.min.y > square_2.max.y)return false;


	// Vector from A to B
	Vec2 deltaDistance = rectPos2 - rectPos1;

	// Calculate half extents along x axis for each object
	float square1_extentX = (square_1.max.x - square_1.min.x) / 2;
	//Half extent
	float square2_extentX = (square_2.max.x - square_2.min.x) / 2;
	//Delta distance X
	//float dx = square1_extentX + square2_extentX;
	// Calculate overlap on x axis
	float x_overlap = (square1_extentX + square2_extentX) - abs(deltaDistance.x);


	// Calculate half extents along x axis for each object
	float square1_extentY = (square_1.max.y - square_1.min.y) / 2;
	//Half extent
	float square2_extentY = (square_2.max.y - square_2.min.y) / 2;
	//Delta distance Y	
	//float dy = square1_extentY + square2_extentY;
	// Calculate overlap on x axis
	float y_overlap = (square1_extentY + square2_extentY) - abs(deltaDistance.y);


	int cp = 0;
	//Collision en X
	if (x_overlap > 0)
	{
		if (y_overlap > 0)
		{
			if (y_overlap > x_overlap)
			{
				if (deltaDistance.x < 0)
				{
					hit.normal = Vec2(-1, 0);
				}
				else
				{
					hit.normal = Vec2(0, 0);
				}
				//Aqui va el hit.contacts
				hit.penetration = x_overlap;
			}
			else
			{
				if (deltaDistance.y < 0)
				{
					hit.normal = Vec2(0, -1);
				}
				else
				{
					hit.normal = Vec2(0, 1);
				}

				hit.penetration = y_overlap;

			}
			//Aqui va el hit.contacts
			hit.contacts_count=1;
		}
	}
	return true;
}




//Todas las de pixels
bool Collider::checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2, Manifold& hit)const
{
	return false;
}

//falta
bool Collider::checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize, Manifold& hit)const
{
	return false;
}

//falta
bool Collider::checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, Manifold& hit)const
{
	return false;
}



//Optional comprobations
bool Collider::CircleCircleUnoptimized(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2, Manifold& hit) const
{
    float dist = Vec2::get_squared_dist(pos2, pos1);
    float radiusSum = radius1 + radius2;

    return radiusSum < dist;      
}
bool Collider::CircleCircleOptimized(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2, Manifold& hit) const
{
    float radiusSum = radius1 + radius2;
    radiusSum *= radiusSum;

    return radiusSum < powf(pos1.GetX() + pos2.GetX(),2) + powf(pos1.GetY() + pos2.GetY(),2);
}