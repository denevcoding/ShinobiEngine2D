#include "stdafx.h"
#include "Sprite.h"
#include "../../Managerx/GraphicsEngine.h"


Sprite::Sprite() //Default Constructor
	: data(nullptr)
	, blendMode(BLEND_SOLID)
	, m_uImgId(NULL)
	, m_sFileName(nullptr)
	, texture(nullptr)

	//, m_currentAnimation() //By default animation
    , hFrames(1)
	, vFrames(1)
	  
	, color{255,255,255,0}
	  
	, angle(0)
	, position(Vec2(0,0))
	, scale(Vec2(0,0))
	, size(Vec2(0,0))
{
	animationList.clear();
	pivot = Vec2(0.5f, 0.5f);//Inherited from render objects
}

Sprite::Sprite(const char* sFileName, int _hframes, int _vframes, Transform2D* _transform)
{
	assert(sFileName != nullptr);

	animationList.clear();
	
	//Setting the sprite by itself
	m_transform_2d = _transform; //Inherit By RenderObject

	m_sFileName = sFileName;
	texture = GraphicsEngine::GetInstance().InsertImg(m_sFileName);	// Get id from repository to render.

	blendMode = BLEND_SOLID;
	
	//For animation
	hFrames = _hframes;
	vFrames = _vframes;

	frameWidth = texture->width / hFrames;
	frameHeight = texture->height / vFrames;

	framesPerRow = texture->width / frameWidth;
	
	//position = _transform->GetPos();
	scale = _transform->GetScale();//Sync the scale with the transform scale
	size  = Vec2(texture->width * scale.x, texture->height * scale.y);
	pivot = Vec2(0.5f, 0.5f); //Pybot in the center by default

	color.R = 255;
	color.G = 255;
	color.B = 255;
	color.A = 255;
}


//Updating Sprite if it has animation
void Sprite::Update(float deltaTime)
{	
	m_currentAnimation.AnimateSprite(deltaTime);	
}

//Render Function because inherits from RenderObject
void Sprite::Render()
{
	position = m_transform_2d->GetPos();
	
	float verticalFrame = m_currentAnimation.currentFrame / hFrames;
	
	float u0 = (float)m_currentAnimation.currentFrame / hFrames;
	float v0 = (float)verticalFrame / vFrames;

	float u1 = (float)(m_currentAnimation.currentFrame + 1) / hFrames;
	float v1 = (float)(verticalFrame + 1) / vFrames;
	
	lgfx_setcolor(color.R, color.G, color.B, color.A);	
	lgfx_setblend(blendMode);

	//lgfx_drawoval(600, 300, 200, 200);
	ltex_drawrotsized(texture, position.x, position.y, angle, pivot.x, pivot.y,
		size.x / hFrames, size.y / vFrames,
		//U0     V0                         
		u0,  v0,
		//U1     V1
		u1, v1);
}


Sprite::~Sprite()
{
	animationList.clear();
	std::cerr << "Se destruido un sprite" << std::endl;
}
