#include "stdafx.h"
#include "GraphicsEngine.h"
#include "../../Global/EngineSettings.h"
//GraphicObjects
#include "../GlobalObjects/Graphix/RenderObject.h"


GraphicsEngine& GraphicsEngine::GetInstance()
{
	static GraphicsEngine engine;
	return engine;
}


void GraphicsEngine::Init()
{
	m_width = GeneralSettings::WindowWidth;
	m_height = GeneralSettings::WindowHeight;

	//mouseX = 0;
	//mouseY = 0;
	window = nullptr;

	m_Images.clear();
	m_RenderObjs.clear();
	m_Colliders.clear();

	glfwSetErrorCallback(error_callback);
	//Initialization	
	if (!glfwInit())
		exit(EXIT_FAILURE);

	if (GeneralSettings::isFullScreen)
	{
	  //Full screen or not
		window = glfwCreateWindow(m_width, m_height, "Shinobi 2D Engine", glfwGetPrimaryMonitor(), nullptr);
	}
	else
	{
		window = glfwCreateWindow(m_width, m_height, "Shinobi 2D Engine", nullptr, nullptr);
	}

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Contexto de window
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	
	//inicializar librería lite
	lgfx_setup2d(m_width, m_height);
}


void GraphicsEngine::Render()
{

    #ifdef  _2D_
		//limpiamos el back buffer
		lgfx_clearcolorbuffer(0, 0, 0);
		//-----------------------------------------------		
		//Bucle principal
		RenderObjs();
		//-----------------------------------------------
		//cambiamos el back por front buffer
		glfwSwapBuffers(window);
	#else	
		//Render3D Objects
	
	#endif

	
}


//Iterate the array of render objects and call the update method
void GraphicsEngine::RenderObjs() const
{
	for (RenderObject* pRenderObj : m_RenderObjs) {
		assert(pRenderObj != nullptr);

		pRenderObj->Render();
	}

	for (Collider* pColliderOBJ : m_Colliders){
		assert(pColliderOBJ != nullptr);
		pColliderOBJ->DrawCollider();
	}
}




void GraphicsEngine::Terminate()
{	
	for (auto itImg = m_Images.begin(); itImg != m_Images.end(); ++itImg) {
		UnloadTexture(itImg->second.ImgTexture);
	}
	
	m_Images.clear();
	m_RenderObjs.clear();
	m_Colliders.clear();

	glfwDestroyWindow(window);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//FONT_End();	// Fonts shutdown.
}





#pragma region Render objects Functions
/*-------------Render Objects-----------------------*/
void GraphicsEngine::InsertRenderObj(RenderObject& renderObj)
{
	// Control if prev. inserted.
	for (const RenderObject* pRenderObj : m_RenderObjs) {
		if (pRenderObj == &renderObj) {
			return;
		}
	}
	m_RenderObjs.push_back(&renderObj);
}

void GraphicsEngine::DeleteRenderObj(RenderObject& renderObj)
{
	for (auto it = m_RenderObjs.begin(); it != m_RenderObjs.end(); ++it) {
		if (*it == &renderObj) {
			m_RenderObjs.erase(it);
			break;
		}
	}
}

void GraphicsEngine::InsertColliderObj(Collider& colliderOBJ)
{
	// Control if prev. inserted.
	for (const Collider* pColliderObj : m_Colliders) {
		if (pColliderObj == &colliderOBJ) {
			return;
		}
	}
	m_Colliders.push_back(&colliderOBJ);
}

void GraphicsEngine::DeleteColliderObj(Collider& colliderOBJ)
{
	for (auto it = m_Colliders.begin(); it != m_Colliders.end(); ++it) {
		if (*it == &colliderOBJ) {
			m_Colliders.erase(it);
			break;
		}
	}
}

/*-------------------------------------------------*/
#pragma endregion







#pragma region Carga imagenes
/*---------------Auxiliares------------------------------*/
ltex_t* GraphicsEngine::InsertImg(const char* sFileName)
{
	tImgInfo* pImgInfo = GetImgInfo(sFileName);
	if (pImgInfo != nullptr)
	{
		pImgInfo->iRefCount++;
		return pImgInfo->ImgTexture;
	}

	//sTexture = loadTexture(sFileName); // rellenamos el letext que viene por parametro
	//unsigned int imgId = reinterpret_cast<unsigned int>(&sTexture);

	assert(sFileName != nullptr);

	tImgInfo newImgInfo;
	newImgInfo.ImgTexture = loadTexture(sFileName);
	newImgInfo.ImgId = reinterpret_cast<unsigned int>(&newImgInfo.ImgTexture);
	newImgInfo.iRefCount = 1;
	m_Images[sFileName] = newImgInfo;
	//return newImgInfo.sTe;
	return newImgInfo.ImgTexture;
}


//Funcion auxiliar paara cargar las texturas
ltex_t* GraphicsEngine::loadTexture(const char* filename) {
	int glid = 0;
	int ancho = 0;
	int alto = 0;
	unsigned char* buffer = stbi_load(filename, &ancho, &alto, nullptr, 4);
	ltex_t* textura = ltex_alloc(ancho, alto, 1); //ltext alloc
	ltex_setpixels(textura, buffer);
	stbi_image_free(buffer);
	return textura;
}



//Funcion para liberar los ltext
void GraphicsEngine::UnloadTexture(ltex_t* l_texture)
{
	ltex_free(l_texture);
}


void GraphicsEngine::DeleteImg(const char* sFileName)
{
	tImgInfo* pImgInfo = GetImgInfo(sFileName);
	if (pImgInfo == nullptr) {
		return;
	}
	pImgInfo->iRefCount--;
	// Image is deleted if it's not used.
	if (pImgInfo->iRefCount == 0) {
		ltex_free(pImgInfo->ImgTexture);
		m_Images.erase(sFileName);
	}
}


GraphicsEngine::tImgInfo* GraphicsEngine::GetImgInfo(const char* sFileName)
{
	// Control if prev. inserted.
	auto result = m_Images.find(sFileName);
	if (result != m_Images.end()) {
		return &result->second;
	}
	return nullptr;
}
#pragma endregion
/*---------------Auxiliares------------------------------*/




