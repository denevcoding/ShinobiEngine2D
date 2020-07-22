#include "stdafx.h"
#include "Animation2D.h"

Animation2D::Animation2D()
:endFrame(1)
,initFrame(1)
,fps(24)//By Default
,animName("Animation")
,currentFrame(0)
{
}

Animation2D::Animation2D(std::string _name, int _fps, int _initFrames, int _animFrames)
{

	animName = _name;
	initFrame = _initFrames;
	endFrame = _animFrames;
	fps = _fps;
	acumTime = 0;
	currentFrame = 0;
	//currentFrame = 0;
}


void Animation2D::AnimateSprite(double _deltatTime)
{
	acumTime = fmod(acumTime + _deltatTime, 1);
	currentFrame = (static_cast<int>(fps * acumTime) % endFrame) + initFrame;
}



Animation2D::~Animation2D()
{
	std::cerr << "Se destruido una Animacion" << std::endl;
}


