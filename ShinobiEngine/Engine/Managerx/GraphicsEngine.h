#pragma once
#ifndef _GRAPHICS_ENGINE_H_
#define _GRAPHICS_ENGINE_H_
#include "../GameObjectx/Components/PhysicComponents/Collider.h"

class RenderObject;

//Classes to get the errors
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


/*This Manager will Handle all about graphics and rendering*/
class GraphicsEngine
{
private: // Manager Variables
	//Window
	GLFWwindow* window;
	
	int m_width;
	int m_height;
	double mouseX, mouseY;

	//To Handle the textures buffers and info on the game on better way
	struct tImgInfo {
		ltex_t* ImgTexture; // Id. image
		unsigned int ImgId;
		unsigned int iRefCount; // Reference counter to unload image if not used		
		tImgInfo() : ImgTexture(nullptr), ImgId(0), iRefCount(0) {}
	};

	// Collection of pairs of name image and renderable info. For memmory purposes.
	std::map<std::string, tImgInfo> m_Images;
	// Array of renderable objects.
	std::vector<RenderObject*>	m_RenderObjs;
	std::vector<Collider*> m_Colliders;


public: // Singleton Settings
	static GraphicsEngine& GetInstance(); //Singleton
	GraphicsEngine(GraphicsEngine const&) = delete; //Delete the default constructor
	void operator = (GraphicsEngine const&) = delete; // Delete the operator to avoid copy constructor

public:	//Manager Cycle
	void Init();
	void Render();
	void Terminate();

public://Auxiliar Functions
	// Insert image inside the repository of images.
	ltex_t* InsertImg(const char* sFileName);
	// Delete image.
	void DeleteImg(const char* sFileName);

	// Insert renderable object.
	void InsertRenderObj(RenderObject& renderObj);
	// Delete renderable object.
	void DeleteRenderObj(RenderObject& renderObj);

	// Insert renderable object.
	void InsertColliderObj(Collider& colliderOBJ);
	// Delete renderable object.
	void DeleteColliderObj(Collider& colliderOBJ);

	
	inline GLFWwindow* Getwindow() { return window; }


private:
	// Private constructor for singleton
	GraphicsEngine() : m_width(0), m_height(0), mouseX(0), mouseY(0), window(nullptr) {};
	// Render objects.
	void RenderObjs() const;
	// Get info image. Returns 0 if error.
	GraphicsEngine::tImgInfo* GetImgInfo(const char* sFileName);

	//Funcion auxiliar para cargar imagenes
	ltex_t* loadTexture(const char* filename);
	void UnloadTexture(ltex_t* l_texture);
	
};
#endif

