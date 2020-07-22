#pragma once
#ifndef _VEC_2_H_
#define _VEC_2_H_

class Vec2
{
public:	
	float x;
	float y;
	
public://cosntructor - Destructor
	Vec2();	
	Vec2(float x, float y);

public://Getters & Setters
	float GetX() const;
	float GetY() const;

	void SetX(float psX);
	void SetY(float psY);


/*-----------METODOS FUNCIONES DE VECTORES 2D-----------------------------*/
	//Distance1
	// distancia 1
	float Lenght();

	// distancia2
	float LenghtSqr();

	static float get_squared_dist(const Vec2& from, const Vec2& to);


	//Normalziar un vector - todas las componentes a 1
	void Normalize(); //  sirven para indicar direccion 

	// add vector to vector
	Vec2 operator+(const Vec2& vhs) const;
	// because user's expect this too
	void operator+=(const Vec2& rhs);
	// add scalar to vector
	Vec2 operator+(float vhs) const;

	
	//convert To negative
	Vec2 operator-(void) const;
	// substract vector to vector
	Vec2 operator-(const Vec2& vhs) const;
	// because user's expect this too
	void operator-=(const Vec2& vhs);
	// Substract scalar to vector
	Vec2 operator-(float vhs) const;


	// Because user expects this too
	void operator*=(float vhs);
	//Multply vector with scalar
	Vec2 operator*(float vhs);

	//float operator*(const Vec2& vhs);


	
	static float dot(const Vec2& a, const Vec2& b);

	// divide vector by scalar
	Vec2 operator/(float vhs);
	// because users expect this too
	Vec2& operator=(const Vec2& vhs);

	bool operator==(const Vec2& vhs);

	


	/*Cross product for rotations*/
	Vec2 Cross(const Vec2& v, float a);

	Vec2 Cross(float a, const Vec2& v);

	static float Cross(const Vec2& a, const Vec2& b);



	Vec2 Min(const Vec2& a, const Vec2& b);
	Vec2 Max(const Vec2& a, const Vec2& b);
	


	//Rotations
	void Rotate(float radians);
	
	
	// angulo y distancia
	// la normal e sun vector ortogonal
	float angle(const Vec2& other)const; // no sabemos si lleva const

	//float distance(const Vec2& va, const Vec2& vb) const;	
	//Vec2 rotar(Vec2 rotante);
};
	


#endif


