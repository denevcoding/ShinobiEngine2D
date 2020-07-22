#pragma once
#ifndef _TRANSFORM_2D_H_
#define _TRANSFORM_2D_H_

#include "Component.h"
#include "../../../Global/MathTools/Vec2.h"


class Transform2D : public Component
{
//Inherited Variables
////Owner
//m_isEnabled
//Transform2D

public:
	Transform2D() :m_vPos(Vec2(0, 0)), m_vScale(Vec2(0, 0)) { m_isEnabled = false; }
	
	Transform2D(Vec2 _position, Vec2 _Scale) : m_vPos(_position), m_vScale(_Scale)
	{ m_transform_2d = nullptr; m_isEnabled = true; }
	
	~Transform2D();

public: //By default
	Vec2 m_vPos;
	Vec2 m_vScale;

public://Component Functions 
	virtual void Update(double ftimeDiff) override;
	virtual void ReceiveMsg(const Message& message) override;
	virtual void Activate()override;
	virtual void Deactivate()override;

public://Getter Setter
	inline const Vec2& GetPos() const { return m_vPos; }
	inline void SetPos(Vec2& vPos) { m_vPos = vPos; }
	
	inline const Vec2& GetScale() const { return m_vScale; }
	inline void SetScale(Vec2& vVel) { m_vScale = vVel; }	
};

#endif



