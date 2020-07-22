#pragma once
#ifndef _ANIMATION__2D_H_
#define _ANIMATION__2D_H_

class Sprite;

class Animation2D
{
public:
	Animation2D();
	Animation2D(std::string _name, int _fps, int _initFrames, int _animFrames);
	~Animation2D();

	void AnimateSprite(double _deltatime);
	
public:
	std::string animName;
	
	//Framing
	int endFrame;	
	int initFrame;
	int currentFrame;

	//Timming
	float acumTime;
	int fps; //Animation Rate - Velocity


public:

	inline const int& GetFrame() const { return currentFrame; }
	inline void SetFrame(int& _frame) { currentFrame = _frame; }

	inline const int& GetAnimFrames() const { return endFrame; }
	inline void SetAnimFrames(int& _animFrames) { endFrame = _animFrames; }

	inline const int& GetInitFrame() const { return initFrame; }
	inline void SetInitFrame(int& _initFrame) { initFrame = _initFrame; }

	inline const int& GetAcumTime() const { return acumTime; }
	inline void SetAcumTime(int& _acumTime) { acumTime = _acumTime; }
	
	inline const int& GetFPS() const { return fps; }
	inline void SetFPS(int& _fps) { fps = _fps; }

	inline const float& GetCurrentFrame() const { return currentFrame; }
	inline void SetCurrentFrame(float& _currentFrame) { currentFrame = _currentFrame; }
};

#endif


