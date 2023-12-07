#pragma once
#include"../baseentity/baseentity.hpp"
#include <assert.h>
#include <random>

#define M_PI 3.14159265
#define RAD_TO_DEG(x) x * (180.f / M_PI)
#define DEG_TO_RAD(x) x * (M_PI / 180.f)

#define DECL_ALIGN(x) __attribute__((aligned(x)))


#define ALIGN16 DECL_ALIGN(16)
#define VALVE_RAND_MAX 0x7fff
#define VectorExpand(v) (v).x, (v).y, (v).z

#define Assert( _exp ) ((void)0)

#define FastSqrt(x)			(sqrt)(x)

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

#define SCREEN_W 1920
#define SCREEN_H 1080
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

struct Matrix {
	float matrix[16];
};

class Vector {
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	inline Vector& operator+=(const Vector& v);
	inline Vector& operator-=(const Vector& v);
	inline Vector& operator*=(const Vector& v);
	inline Vector& operator*=(float s);
	inline Vector& operator/=(const Vector& v);
	inline Vector& operator/=(float s);
	inline Vector& operator+=(float fl);
	inline Vector& operator-=(float fl);
	inline float	Length() const;
	inline float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	Vector	Normalize();
	void	NormalizeInPlace();
	inline float	DistTo(const Vector& vOther) const;
	inline float	DistToSqr(const Vector& vOther) const;
	float	Dot(const Vector& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	Vector& operator=(const Vector& vOther);
	Vector	operator-(void) const;
	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

class Vector2D {
public:
	float x, y;
	Vector2D(void);
	Vector2D(float X, float Y);
	Vector2D(const float* pFloat);

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	// arithmetic operations
	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator*=(float s);
	Vector2D& operator/=(const Vector2D& v);
	Vector2D& operator/=(float s);

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	float	Length() const;

	// Get the Vector2D's magnitude squared.
	float	LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	float	Normalize();

	// Normalize in place and return the old length.
	float	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// Get the distance from this Vector2D to the other one.
	float	DistTo(const Vector2D& vOther) const;

	// Get the distance from this Vector2D to the other one squared.
	float	DistToSqr(const Vector2D& vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

	// Dot product.
	float	Dot(const Vector2D& vOther) const;

	// assignment
	Vector2D& operator=(const Vector2D& vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	Vector2D(const Vector2D& vOther);

	// arithmetic operations
	Vector2D	operator-(void) const;

	Vector2D	operator+(const Vector2D& v) const;
	Vector2D	operator-(const Vector2D& v) const;
	Vector2D	operator*(const Vector2D& v) const;
	Vector2D	operator/(const Vector2D& v) const;
	Vector2D	operator*(float fl) const;
	Vector2D	operator/(float fl) const;

	// Cross product between two vectors.
	Vector2D	Cross(const Vector2D& vOther) const;

	// Returns a Vector2D with the min or max in X, Y, and Z.
	Vector2D	Min(const Vector2D& vOther) const;
	Vector2D	Max(const Vector2D& vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector2D(const Vector2D& vOther);
#endif
};

namespace engine
{
	/*
		for apex do pOffsets.pApex.m_vViewRender
		for warzone do pOffsets.pWarzone.m_nViewRender
		etc
	*/
	__inline Matrix GetViewMatrix()
	{
		uint64_t ViewRenderer = *(uint64_t*)(pOffsets.module_base + pOffsets.pDeadByDaylight.m_vVewRender);
	}
	__inline bool WorldToScreen(Vector In, Vector2D& Out)
	{
		float* m_vMatrix = GetViewMatrix().matrix;
		float w = m_vMatrix[12] * In.x + m_vMatrix[13] * In.y + m_vMatrix[14] * In.z + m_vMatrix[15];

		if (w < 0.01f)
			return false;

		Out.x = m_vMatrix[0] * In.x + m_vMatrix[1] * In.y + m_vMatrix[2] * In.z + m_vMatrix[3];
		Out.y = m_vMatrix[4] * In.x + m_vMatrix[5] * In.y + m_vMatrix[6] * In.z + m_vMatrix[7];

		float invw = 1.0f / w;
		Out.x *= invw;
		Out.y *= invw;

		float xx = GetSystemMetrics(SM_CXSCREEN) / 2;
		float xy = GetSystemMetrics(SM_CYSCREEN) / 2;

		xx += 0.5 * Out.x * GetSystemMetrics(SM_CXSCREEN) + 0.5;
		xy -= 0.5 * Out.y * GetSystemMetrics(SM_CYSCREEN) + 0.5;

		Out.x = xx;
		Out.y = xy;

		if (Out.x > GetSystemMetrics(SM_CXSCREEN) || Out.x < 0 || Out.y > GetSystemMetrics(SM_CYSCREEN) || Out.y < 0)
			return false;

		return true;
	}
}