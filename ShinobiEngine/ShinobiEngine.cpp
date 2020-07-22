// ShinobiEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define STB_IMAGE_IMPLEMENTATION
#define LITE_GFX_IMPLEMENTATION


#include "stdafx.h"
#include "Engine/Managerx/GraphicsEngine.h"
#include "Engine/Managerx/World.h"
#include "Engine/Managerx/PhysixEngine.h"
#include "Engine/Managerx/AudioManager.h"

int main()
{
	//Initializing Shinobi Engine
	AudioManager::GetInstance().Init();
	GraphicsEngine::GetInstance().Init();	
	PhysixEngine::GetInstance().Init();
	World::GetInstance().Init();
	
	//Shinobi Main Loop Engine
	while (!glfwWindowShouldClose(GraphicsEngine::GetInstance().Getwindow()))
	{	// Controlling a request to terminate an application.		
		World::GetInstance().Update();
		PhysixEngine::GetInstance().PhysixUpdate();
		GraphicsEngine::GetInstance().Render();
		AudioManager::GetInstance().AudioUpdate();
		glfwPollEvents();
	}

	//Shut Down Engine
	World::GetInstance().Terminate();
	PhysixEngine::GetInstance().Terminate();	
	GraphicsEngine::GetInstance().Terminate();
	AudioManager::GetInstance().Terminate();
}

