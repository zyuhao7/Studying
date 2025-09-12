#include <assert.h>
#include <math.h>


#include "vector3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "RotationMatrix.h"
#include "MathUtil.h"
#include "Matrix4x3.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ��������Ŀ����Ϊ�˱���ʹ�ã� �û����÷����ı������Ż���ת��֪���������������ȷ������Ȼ���ڲ�ʵ�ֵ�ϸ���Ǻ���Ҫ��
// ������Ϊ�����ʵ�ֵ���ȷ�ԣ�ҲΪ��żȻ���ܷ����ĶԾ���Ԫ�ص�ֱ�ӷ��ʣ�����Ϊ���Ż�
// ��ˣ� ��������һ�¾��������õ�Լ��
//����ʹ�������������Ծ���˷���ʽ���£�
//		      |m11 m12 m13|     
//			  |m21 m22 m23|   
// |x y z| *  |m31 m32 m33| = |x' y' z'|
//			  |tx  ty  tz |
//
//�����ϸ�����Դ����������ֳ˷��ǲ������ġ�
//���ǿ��Լ��裬�������������е��ĸ���������Ϊ1
//���⣬����4x3�����ǲ�������ģ� ��˼�������е�4�У�Ϊ[0 0 0 1]
//������ʾ��
//
//               |m11 m12 m13 0|   
//			     |m21 m22 m23 0|   
//   |x y z 1| * |m31 m32 m33 0| = |x' y' z' 1|
//               |tx  ty  tz  1|   
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix4x3 ���Ա
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
// Matrix4x3::identity
// ��Ϊ��λ����

void Matrix4x3::identity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	tx = 0.0f; ty = 0.0f; tz = 0.0f;
}

//----------------------------------------------------------------------------------------------------
// Matrix4x3::zeroTranslation
//������ƽ�Ʋ��ֵĵ�������Ϊ��

void Matrix4x3::zeroTranslation()
{
	tx = ty = tz = 0.0f;
}

//----------------------------------------------------------------------------------------------------
// Matrix4x3::setTranslation
//ƽ�Ʋ��ָ�ֵ������Ϊ������ʽ

void Matrix4x3::setTranslation(const Vector3& d)
{
	tx = d.x; ty = d.y; tz = d.z;
}

//----------------------------------------------------------------------------------------------------
// Matrix4x3::setupTranslation
//����ƽ�ƾ��󣬲���Ϊ������ʽ

void Matrix4x3::setupTranslation(const Vector3& d)
{
	//���Ա任������Ϊ��λ����
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;

	// ƽ�Ʋ��ָ�ֵ
	tx = d.x; ty = d.y; tz = d.z;
}

//----------------------------------------------------------------------------------------------
// Matrix4x3::setupLocalToParent
// ����ִ�оֲ�->���ռ�任�ľ��󣬾ֲ��ռ��λ�úͷ�Χ�ڸ��ռ�������
// �÷����������;�ǹ�������->����ı任��������任�Ƿǳ�ֱ�ӵġ�
// ���ȴ�����ռ�任�����Կռ䣬���ű任������ռ�
// ��λ������ŷ���Ǻ���ת����ָ��

void Matrix4x3::setupLocalToParent(const Vector3& pos, const EulerAngles& orient)
{
	// ����һ����ת����
	RotationMatrix orientMatrix;
	orientMatrix.setup(orient); // ��ŷ���ǹ���һ����ת����

	// ����4x3����
	setupLocalToParent(pos, orientMatrix);

}

void Matrix4x3::setupLocalToParent(const Vector3& pos, const RotationMatrix& orient)
{
	// ���ƾ������ת����
	//����RotationMatrix �е�ע�ͣ���ת����һ�㡱�ǹ���-�������
	//�Ǹ�-�ֲ���ϵ
	//��������Ǿֲ�-����ϵ�ľ������Ҫ��ת��
	m11 = orient.m11; m12 = orient.m21; m13 = orient.m31;
	m21 = orient.m12; m22 = orient.m22; m23 = orient.m32;
	m31 = orient.m13; m32 = orient.m23; m33 = orient.m33;

	// ��������ƽ�Ʋ���, ƽ����3x3����֮��, �������ֻ��򵥸�����λ�ü���
	tx = pos.x; ty = pos.y; tz = pos.z;
}

//-------------------------------------------------------------------------------------------------
// Matrix4x3::setupParentToLocal
// ����ִ�и�-�ֲ��ռ�任�ľ��󣬾ֲ��ռ��λ�úͷ�λ�ڸ��ռ�������
// �÷����������;�ǹ�������-����ı任����
// ͨ������任���ȴ�����ת�������Կռ䣬����ת��������ռ�
// 4x3 ���������ɺ�һ��ת��
// ���������빹����������T��R��������M=TR
// ��λ������ŷ���ǻ���ת����ָ��

void Matrix4x3::setupParentToLocal(const Vector3& pos, const EulerAngles& orient)
{
	// ����һ����ת����
	RotationMatrix orientMatrix;
	orientMatrix.setup(orient);

	// ���� 4x3 ����
	setupParentToLocal(pos, orientMatrix);
}

void Matrix4x3::setupParentToLocal(const Vector3& pos, const RotationMatrix& orient)
{
	// ���ƾ������ת����
	// ����ֱ�Ӹ���Ԫ��
	m11 = orient.m11; m12 = orient.m12; m13 = orient.m13;
	m21 = orient.m21; m22 = orient.m22; m23 = orient.m23;
	m31 = orient.m31; m32 = orient.m32; m33 = orient.m33;

	// ����ƽ�Ʋ���
	// һ����˵��������ռ䵽���Կռ�ֻ��Ҫƽ�Ƹ�����
	// ������ǵ���ת�ǡ��ȡ������ģ�����Ӧ����תƽ�Ʋ���
	// ����ȴ���ƽ��-pos�ľ����ٴ�����ת����R��
	// �ٰ��������ӳ�TR��һ����
	tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
	ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
	tz = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
}

//------------------------------------------------------------------------------------------
// Matrix4x3::setupRotate
// ��������������ת�ľ���
// ��ת���1��ʼ����ָ��
//
// 1 => ��x����ת
// 2 => ��y����ת
// 3 => ��z����ת
// theta ����ת�����Ի��ȱ�ʾ�������ַ����塰������
//	ƽ�Ʋ�������

void Matrix4x3::setupRotate(int axis, float theta)
{
	// ȡ����ת�ǵ� cos �� sin ֵ
	float s, c;
	sinCos(&s, &c, theta);

	// �ж���ת��
	switch (axis)
	{
	case 1: // �� x ����ת
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c; m23 = s;
		m31 = 0.0f; m32 = -s; m33 = c;
		break;

	case 2: // �� y ����ת
		m11 = c; m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = 0.0f; m33 = c;
		break;

	case 3: // �� z ����ת
		m11 = c; m12 = s; m13 = 0.0f;
		m21 = -s; m22 = c; m23 = 0;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	default:
		//�Ƿ�����
		assert(false);
	}

	tx = ty = tz = 0.0f;
}

//-------------------------------------------------------------------------------------------------------
// Matrix4x3::setupRotate
// ��������������ת��������ͨ��ԭ��
// ��ת��Ϊ��λ����
// theta ����ת�������Ի��ȱ�ʾ�������ַ���������"������"
// ƽ�Ʋ�������

void Matrix4x3::setupRotate(const Vector3& axis, float theta)
{
}

void Matrix4x3::fromQuaternion(const Quaternion& q)
{
}

void Matrix4x3::setupScale(const Vector3& s)
{
}

void Matrix4x3::setupScaleAlongAxis(const Vector3& axis, float k)
{
}

void Matrix4x3::setupShear(int axis, float s, float t)
{
}

void Matrix4x3::setupProject(const Vector3& n)
{
}

void Matrix4x3::setupReflect(int axis, float k)
{
}

void Matrix4x3::setupReflect(const Vector3& n)
{
}

Vector3 operator*(const Vector3& p, const Matrix4x3& m)
{
	return Vector3();
}

Matrix4x3 operator*(const Matrix4x3& a, const Matrix4x3& b)
{
	return Matrix4x3();
}

Vector3& operator*=(Vector3& p, const Matrix4x3& m)
{
	// TODO: �ڴ˴����� return ���
}

Matrix4x3& operator*=(Matrix4x3& a, const Matrix4x3& m)
{
	// TODO: �ڴ˴����� return ���
}

float determinant(const Matrix4x3& m)
{
	return 0.0f;
}

Matrix4x3 inverse(const Matrix4x3& m)
{
	return Matrix4x3();
}

Vector3 getTranslation(const Matrix4x3& m)
{
	return Vector3();
}

Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m)
{
	return Vector3();
}

Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3& m)
{
	return Vector3();
}
