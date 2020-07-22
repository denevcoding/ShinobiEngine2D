#pragma once
#ifndef  _RENDER_COMPONENT_H_
#define  _RENDER_COMPONENT_H_
#include "../Component.h"
#include "../../../GlobalObjects/Graphix/Sprite.h"

class Transform2D;


class RenderComponent : public Component
{
	//Inherited Variables
	////Owner
	//m_isEnabled
	//Transform2D
	
public://Constructor - Destructor
	RenderComponent();
	RenderComponent(Transform2D* _transform, const char* _spriteRoot, int _hFrames, int _vFrames);
	~RenderComponent();

public://Variables
	Sprite m_Sprite; //Sprite Associated

public://Component Functions
	virtual void Update(double fTimeDif) override;
	virtual void ReceiveMsg(const Message& message) override;	
	virtual void Activate()override;
	virtual void Deactivate()override;

public://Getters Setters
	inline Sprite GetSprite() { return m_Sprite; }
	inline void SetSprite(Sprite _sprite) { m_Sprite = _sprite; }
	
};
#endif

