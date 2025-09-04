#pragma once
#include <iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
//  Vector3 �� �򵥵� 3D ������
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

	// ��� C ���Է��, ���ظ�ֵ�����, Ȼ�󷵻�����, ��ʵ����ֵ
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

	//��������
	// ��Ϊ������
	void zero() { x = y = z = 0.0f; }

	// ����һԪ `-` �����
	Vector3 operator-() const { return Vector3{ -x, -y, -z }; }

	// ���ض�Ԫ `+` �� `-` �����
	Vector3 operator+(const Vector3& v3) const
	{
		return Vector3(x + v3.x, y + v3.y, z + v3.z);
	}
	Vector3 operator-(const Vector3& v3) const
	{
		return Vector3(x - v3.x, y - v3.y, z - v3.z);
	}

	// ������ĳˡ�����
	Vector3 operator* (float a) const
	{
		return Vector3(x * a, y * a, z * a);
	}
	Vector3 operator/ (float a) const
	{
		float oneOverA = 1.0f / a;			// ���ﲻ�� "����" ���м��
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}

	// �����Է������
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

	// ������׼��
	void normalize()
	{
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f) // ������
		{
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}
	// �������, ���ر�׼�ĳ˷������
	float operator*(const Vector3& v3) const
	{
		return x * v3.x + y * v3.y + z * v3.z;
	}
};

//////////////////////////////////////////////////////////////////////////////
// �ǳ�Ա����
//////////////////////////////////////////////////////////////////////////////

// ������ģ
inline float vectorMag(const Vector3& v3)
{
	return sqrt(v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
}

// �����������Ĳ��
inline Vector3 crossProduct(const Vector3& a, const Vector3& b)
{
	return Vector3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

// ʵ�ֱ������
inline Vector3 operator*(float k, const Vector3& v3)
{
	return Vector3(k * v3.x, k * v3.y, k * v3.z);
}

// ���������ľ���
inline float distance(const Vector3& a, const Vector3& b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

//////////////////////////////////////////////////////////////////////////////
//ȫ�ֱ���
//////////////////////////////////////////////////////////////////////////////

// �ṩһ��ȫ��������
extern const Vector3 kZeroVector;