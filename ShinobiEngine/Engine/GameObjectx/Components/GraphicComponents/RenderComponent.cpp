#include "stdafx.h"
#include "RenderComponent.h"
#include "../Transform2D.h"
#include "../ShinobiEngine/Engine/GameObjectx/GameObject.h"
#include "../../../Managerx/GraphicsEngine.h"

RenderComponent::RenderComponent()
{
	m_isEnabled = false;
	m_Sprite = Sprite();//Default sprite
	m_transform_2d = this->GetOwner()->FindComponent<Transform2D>();
}

RenderComponent::RenderComponent(Transform2D* _transform, const char* _spriteRoot, int _hFrames, int _vFrames)
	: m_Sprite(_spriteRoot, _hFrames, _vFrames, _transform)
{	
	m_transform_2d = _transform;
	m_isEnabled = true;
	//Registering rendereable object in graphics engine
	GraphicsEngine::GetInstance().InsertRenderObj(m_Sprite);
}





void RenderComponent::Update(double fTimeDif)
{
	m_Sprite.Update(fTimeDif);
}

void RenderComponent::ReceiveMsg(const Message& message)
{
}

void RenderComponent::Activate()
{
	m_isEnabled = true;
}

void RenderComponent::Deactivate()
{
	m_isEnabled = false;
}






RenderComponent::~RenderComponent()
{
	std::cerr << "Se destruido un Tansform 2D" << std::endl;
	//DesRegistering rendereable object in graphics engine
	GraphicsEngine::GetInstance().DeleteRenderObj(m_Sprite);
}
