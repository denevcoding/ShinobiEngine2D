#pragma once
#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_

#include "../../../Global/MathTools/Vec2.h"
#include "../../GameObjectx/Components/Transform2D.h"


//Struct Color for color  rendering
struct Color { int R; 	int G; 	int B; 	int A; };


class RenderObject
{
public://Variables
	Transform2D* m_transform_2d;
	Vec2 pivot;

public://Constructor
	RenderObject(): m_transform_2d(nullptr), pivot(Vec2(0,0)) {};
	virtual void Render() = 0;	
};
#endif
