#include "stdafx.h"
#include "Transform2D.h"


Transform2D::~Transform2D()
{
	std::cerr << "Se destruido un Tansform 2D" << std::endl;
}

void Transform2D::Update(double ftimeDiff)
{
}

void Transform2D::ReceiveMsg(const Message& message)
{
}

void Transform2D::Activate()
{
	m_isEnabled = true;
}

void Transform2D::Deactivate()
{
	m_isEnabled = false;
}
