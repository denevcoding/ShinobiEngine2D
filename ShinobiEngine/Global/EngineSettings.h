#pragma once
#ifndef _GLOBAL_SETTINGS_H_
#define _GLOBAL_SETTINGS_H_


//Use this header to set some default variables of the some Managers on the Engine

//This name space contains glogal Setting for window height 
namespace GeneralSettings
{
	constexpr unsigned int WindowWidth{ 1280 };
	constexpr unsigned int WindowHeight{ 720 };
    constexpr bool isFullScreen(false);
}

//Define Settings for the graphic Manager
namespace GraphicSettings
{
   #define _2D_ //or 2D
}

//Define settings for the input Manager
namespace InputSettings
{
	
}

//Definie Seetings for the Time Manager
namespace TimeSettings
{
    constexpr double fps = 60.f;
    constexpr double DeltaTime = 1.0f / fps;
}

//Here we define the default mass gravity and physic stuffs
namespace PhysicxSettings {
    constexpr bool bScreenBorders{ true };

    constexpr bool bExplicitEuler{ false };

    constexpr bool bUseOptimizedCollitions{ false };
	
    constexpr double PhysicsDeltaTime = 1.0f / 60.f;
    constexpr int iIterations = 10;
	
    constexpr float PI = 3.141592741f;
    constexpr float EPSILON = 0.0001f;

    constexpr float gravityScale = 5.0f;
    constexpr double GravityX = 0.f;
    constexpr double GravityY = 10.f;
	
   // const float fMaxVelSpeed{ 8.0f * 60.0f }; 
}

//Here we defines the default behaviour of the audio
namespace AudioSettings {}

//Defines the main rules on the game -- Lifes -- Bullets -- Enemies -- So on
namespace GameMode {
    //Player
    constexpr float vInitPlayerPosX = GeneralSettings::WindowWidth / 2.0f;
    constexpr float vInitPlayerPosY = GeneralSettings::WindowHeight / 2.0f;
    constexpr int iCantLifes{ 10 };
    constexpr int iMaxBulletWorld{ 5 };

    //Enemies
    constexpr int iEnemiesPool{ 2 };

    //UI
    constexpr int iLifesHudX{ 500 };
    constexpr int iLifesHudY{ 50 };

    constexpr int iSpawnPosibilityTime{ 300 };

    //Resources and so on
    constexpr int iPosOutScreenX = -50;
    constexpr int iPosOutScreenY = -50;
    //constexpr int iBallsRadius{ 12 };
}


#endif
