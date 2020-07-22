#include "stdafx.h"
#include "Vec2.h"
#include "../EngineSettings.h"

/*---------CONSRUCTORES-----------*/

// cosntructor predeterminado
Vec2::Vec2()
: x(0)
, y(0)
{
	x = 0;
	y = 0;
}

// Constrcutor Initialization
Vec2::Vec2(float _posX, float _posY) {
	x = _posX;
	y = _posY;
}

// Getters y setters de las variables
float Vec2::GetX() const {
	return x;
}
float Vec2::GetY() const {
	return y;
}

void Vec2::SetX(float psX) {
	x = psX;
}
void Vec2::SetY(float psY) {
	y = psY;
}


/*--------- FUNCIONES DE LOS VECTORES -----------*/
//-------------------------------------------------
float Vec2::Lenght()
{
	//The magnitude of the vector
    return sqrtf(pow(x, 2) + pow(y, 2));
}
float Vec2::LenghtSqr()
{
	//squared lenght for distances
	return x * x + y * y;
}
float Vec2::get_squared_dist(const Vec2& from, const Vec2& to)
{		
	return sqrtf(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));;
}

// Todas las componentes a 1
void Vec2::Normalize()
{
	float len = Lenght();
	if (len > PhysicxSettings::EPSILON) {
		const float invLen = 1.0f / len;
		x *= invLen;
		y *= invLen;
		//return vr;
	}	
}

// Add vector to vector
Vec2 Vec2::operator+(const Vec2& vhs)const
{
	Vec2 vc;
	vc.x = x + vhs.x;
	vc.y = y + vhs.y;
	return vc;
}
//Because user expects this too 
void Vec2::operator+=(const Vec2& vhs)
{
	x += vhs.x;
	y += vhs.y;
	//return *this;//itself
}
// Add scalar to a vector
Vec2 Vec2::operator+(float vhs) const
{
	Vec2 vc;
	vc.x = x + vhs;
	vc.y = y + vhs;
	return vc;
}


//Convert to Negative
Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

//Substract Vector to a vector
Vec2 Vec2::operator-(const Vec2& vhs) const {
	Vec2 vc;
	vc.x = x - vhs.x;
	vc.y = y - vhs.y;
	return vc;
}
//Because user expects this too
void Vec2::operator-=(const Vec2& vhs) {
	Vec2 vc;
	x -= vhs.x;
	y -= vhs.y;
	//return *this;
}
//Substrac a vector with a scalar
Vec2 Vec2::operator-(float vhs) const {
	Vec2 vc;
	vc.x = x - vhs;
	vc.y = y - vhs;
	return vc;
}



//Multiply vector with vector
void Vec2::operator*=(float vhs) {
	x  *= vhs;
	y  *= vhs;
	//return *this;
}
//Because user expects this too

//Multiply vector with scalar
Vec2 Vec2::operator*(float vhs) {
	Vec2 vc;
	vc.x = x * vhs;
	vc.y = y * vhs;
	return vc;
}

//float Vec2::operator*(const Vec2& vhs)
//{
//	float 
//	return 
//}


//Dot product to get angles too
float Vec2::dot(const Vec2& a, const Vec2& b) {
	return a.x * b.x + a.y * b.y;
}

// Divide Vector by scalar
Vec2 Vec2::operator/(float vhs) {
	Vec2 vc;
	vc.x = x / vhs;
	vc.y = y / vhs;
	return vc;
}

// Equals Vector to a vector
Vec2& Vec2::operator=(const Vec2& vhs) {
	x = vhs.x;
	y = vhs.y;
	return *this;
}


/*Cross product for rotations*/
Vec2 Vec2::Cross(const Vec2& v, float a)
{
	return Vec2(a * v.y, -a * v.x);
}

Vec2 Vec2::Cross(float a, const Vec2& v)
{
	return Vec2(-a * v.y, a * v.x);
}

float Vec2::Cross(const Vec2& a, const Vec2& b)
{
	return a.x * b.y - a.y * b.x;
}



// Min Max Vector 
Vec2 Vec2::Min(const Vec2& a, const Vec2& b)
{
	return Vec2(min(a.x, b.x), min(a.y, b.y));
}

Vec2 Vec2::Max(const Vec2& a, const Vec2& b)
{
	return Vec2(max(a.x, b.x), max(a.y, b.y));
}






void Vec2::Rotate(float radians)
{
	float cos = cosf(radians);
	float sin = sinf(radians);

	float xp = x * cos - y * sin;
	float yp = x * sin + y * cos;

	x = xp;
	y = yp;
}


// hacer que se rote sobnre un eje
//Vec2 Vec2::rotar(Vec2 rotante) {
//	Vec2 rotacion = Vec2(rotante.x + cos(speed) * 100, rotante.y + sin(speed) * 100);
//	return rotacion;
//}

// Obtener el angulo
float Vec2::angle(const Vec2& other)const {
	float angulo = (float)atan2(other.y - y, other.x - x);
	return angulo;
}

bool Vec2::operator==(const Vec2& vhs)
{
	if (this->y == vhs.y && this->x == vhs.x)
	{
		return true;
	}
	return false;
}