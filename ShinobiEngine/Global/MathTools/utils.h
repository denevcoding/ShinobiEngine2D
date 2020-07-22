#pragma once
#include "../EngineSettings.h"

#include<cassert>
#include <cmath>

class Vec2;

class Utils
{
public:
	template<class T>
	static constexpr const T& clamp(const T& v, const T& lo, const T& hi)
	{
		assert(!(hi < lo));
		return (v < lo) ? lo : (hi < v) ? hi : v;
	}

	static float Clamp2(float min, float max, float a)
	{
		if (a < min) return min;
		if (a > max) return max;
		return a;
	}
	

	static float PythagoreanSolve(float valueA, float valueB)
	{
		return powf(valueA, 2) + powf(valueB,2);
	}

	// Comparison with tolerance of EPSILON
	static bool Equal(float valueA, float valueB)
	{
		return abs(valueA - valueB) <= PhysicxSettings::EPSILON;
	}

	static float Random(float low, float high)
	{
		float randomValue = (float)rand();
		randomValue /= RAND_MAX;
		randomValue = (high - low) * randomValue + low;
		return randomValue;
	}

	static int Round(float value)
	{
		return (int)(value + 0.5f);
	}

	static float Sqr(float value)
	{
		return value * value;
	}
	   
	
	/*
	inline bool BiasGreaterThan(real a, real b)
	{
		const real k_biasRelative = 0.95f;
		const real k_biasAbsolute = 0.01f;
		return a >= b * k_biasRelative + a * k_biasAbsolute;
	}*/
	
};
