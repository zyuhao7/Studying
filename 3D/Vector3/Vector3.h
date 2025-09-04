#pragma once
#include <iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
//  Vector3 类 简单的 3D 向量类
//////////////////////////////////////////////////////////////////////////////
class Vector3
{
public:
	float x, y, z;
	Vector3()
	:x(0.0),
	y(0.0),
	z(0.0)
	{}

	Vector3(const Vector3& v3)
		:x(v3.x),
		y(v3.y),
		z(v3.z)
	{}

	Vector3(float nx, float ny, float nz)
		:x(nx),
		y(ny),
		z(nz)
	{}

	// 坚持 C 语言风格, 重载赋值运算符, 然后返回引用, 来实现左值
	Vector3& operator=(const Vector3& v3)
	{
		x = v3.x;
		y = v3.y;
		z = v3.z;
		return *this;
	}

	bool operator==(const Vector3& v3) const
	{
		return x == v3.x && y == v3.y && z == v3.z;
	}

	//向量运算
	// 置为零向量
	void zero() { x = y = z = 0.0f; }

	// 重载一元 `-` 运算符
	Vector3 operator-() const { return Vector3{ -x, -y, -z }; }

	// 重载二元 `+` 和 `-` 运算符
	Vector3 operator+(const Vector3& v3) const
	{
		return Vector3(x + v3.x, y + v3.y, z + v3.z);
	}
	Vector3 operator-(const Vector3& v3) const
	{
		return Vector3(x - v3.x, y - v3.y, z - v3.z);
	}

	// 与标量的乘、除法
	Vector3 operator* (float a) const
	{
		return Vector3(x * a, y * a, z * a);
	}
	Vector3 operator/ (float a) const
	{
		float oneOverA = 1.0f / a;			// 这里不对 "除零" 进行检查
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}

	// 重载自反运算符
	Vector3& operator +=(const Vector3& v3)
	{
		x += v3.x; y += v3.y; z += v3.z;
		return *this;
	}
	Vector3& operator -=(const Vector3& v3)
	{
		x -= v3.x; y -= v3.y; z -= v3.z;
		return *this;
	}
	Vector3& operator *=(float a)
	{
		x *= a; y *= a; z *= a;
		return *this;
	}
	Vector3& operator /=(float a)
	{
		float oneOverA = 1.0f / a;
		x *= oneOverA; y *= oneOverA; z *= oneOverA;
		return *this;
	}

	// 向量标准化
	void normalize()
	{
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f) // 检查除零
		{
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}
	// 向量点乘, 重载标准的乘法运算符
	float operator*(const Vector3& v3) const
	{
		return x * v3.x + y * v3.y + z * v3.z;
	}
};

//////////////////////////////////////////////////////////////////////////////
// 非成员函数
//////////////////////////////////////////////////////////////////////////////

// 求向量模
inline float vectorMag(const Vector3& v3)
{
	return sqrt(v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
}

// 计算两向量的叉乘
inline Vector3 crossProduct(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

// 实现标量左乘
inline Vector3 operator*(float k, const Vector3& v3)
{
	return Vector3(k * v3.x, k * v3.y, k * v3.z);
}

// 计算两点间的距离
inline float distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

//////////////////////////////////////////////////////////////////////////////
//全局变量
//////////////////////////////////////////////////////////////////////////////

// 提供一个全局零向量
extern const Vector3 kZeroVector;