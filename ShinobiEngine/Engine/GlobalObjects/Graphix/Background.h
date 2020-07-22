#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "RenderObject.h"
#include "Sprite.h"

class Background : public RenderObject
{
	//Inherited Varaiables
	// Transform 2D
	// Vec2 Pivot
	
public://Constructor Destructor
	Background();
	Background(const char* sFileName, int _hFrames, int _vFrames, Transform2D* _transform);
	~Background();
	
public: //Member Variables
	Sprite m_sprite;

	//Render Object Functions

public:
	//Render Object Fuction Called from Graphic Engine when it is registered
	void Render() override;

public://Gettes Setters
	inline Sprite GetSprite() const { return m_sprite; }
};

#endif


