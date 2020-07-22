#include "stdafx.h"
#include "Background.h"

Background::Background() :m_sprite()
{
	m_transform_2d = nullptr;
	pivot = Vec2(0, 0);
}

Background::Background(const char* sFileName, int _hFrames, int _vFrames, Transform2D* _transform)
	:m_sprite(sFileName, _hFrames, _vFrames, _transform)
{
	
	m_transform_2d = _transform;
	pivot = Vec2(0, 0);
	m_sprite.SetPivot(pivot);
}

void Background::Render()
{
	m_sprite.Render();
}

Background::~Background()
{
	//delete(m_transform_2d)
	std::cerr << "Se destruido un Background" << std::endl;
}

