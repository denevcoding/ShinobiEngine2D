#pragma once

#include "RenderObject.h"
#include "../../../Global/MathTools/Vec2.h"
#include "../Animationx/Animation2D.h"


class Transform2D;

class Sprite : public RenderObject
{
	//Inherited Varaiables
	// Transform 2D
	// Vec2 Pivot 
	
public: //Constructor Destructor
	Sprite();
	// Indicamos el número de frames en horizontal y vertical // que tendrá la imagen del Sprite
	Sprite(const char* sFileName, int _hframes, int _vframes, Transform2D* _transform);
	~Sprite();//destructor
	
public: // Member Variables.
	//-----Data & Image-----
	void* data;
	lblend_t blendMode;
	ltex_t* texture;
	unsigned int m_uImgId;//LtexID
	const char* m_sFileName;// File name.
	Color color;
			
	//-----Time - FPS----
	std::vector<Animation2D*> animationList;
	Animation2D m_currentAnimation;
	int hFrames;
	int vFrames;
	float frameWidth;
	float frameHeight;	
	int framesPerRow;




	//-------Movement - Position------------
	Vec2 position;
	float angle;
	Vec2 scale;
	Vec2 size;

public:
	void Render(void) override;
	void Update(float deltaTime);

	static void AnimateSprite(Sprite m_sprite, float _frameWidth, float _frameHeight, int _endFrames);
	
	
	//Tipo de la función callback
	typedef void (*CallbackFunc)(Sprite&, float);
	// Establecemos puntero a la función callback
	void setCallback(CallbackFunc func);
	CallbackFunc* funcCalllBack;


	
public: //----- INILINE Getters & setters///
// Puntero genérico a datos (normalmente introducimos aquí los datos
// del sprite que se van a utilizar en la función callback)
	inline void* getUserData() { return data; }
	inline void setUserData(void* _data) { data = _data; }

	// Texture Variables
	inline const ltex_t* GetTexture() const { return texture; }
	inline void SetTexture(ltex_t* _tex, int hframes = 1, int vframes = 1) { texture = _tex; }
	inline lblend_t GetBlend() const { return blendMode; }
	inline void SetBlend(lblend_t _blendmode) { blendMode = _blendmode; }

	//COLORS Func
	inline Color GetColor()const { return color; }
	inline void setColor(Color _color) { color = _color; }

	//VEC2 Funcs
	inline const Vec2& GetPosition() const { return position; }
	inline void SetPosition(const Vec2& pos) { position = pos; }

	inline float GetAngle() const { return angle; }
	inline void SetAngle(float _angle) { angle = _angle; }

	inline const Vec2& GetScale() const { return scale; }
	inline void SetScale(const Vec2& _scale) { scale = _scale; }

	// Tamaño de un frame multiplicado por la escala
	inline Vec2 GetSize() const { return size; }
	inline void SetSize(const Vec2& _size) { size = _size; }

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	inline const Vec2& GetPivot() const { return pivot; }
	inline void SetPivot(const Vec2& _pivot) { pivot = _pivot; }

	//ANIMATION Settings
	inline int GetHframes() const { return hFrames; }
	inline void SetHFrames(int _hframes) { hFrames = _hframes; }
	inline int GetVframes() const { return vFrames; }
	inline void SetVframes(int _vFrames) { vFrames = _vFrames; }

	inline float GetFrameWidth()const { return frameWidth; }
	inline float GetFrameHeight()const { return frameHeight; }

	//Getter y Stteer de animation -- Saber como integrar la clase animation
};

