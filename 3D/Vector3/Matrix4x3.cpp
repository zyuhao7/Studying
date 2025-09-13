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
	// ������Ƿ�Ϊ��λ����
	assert(fabs(axis * axis - 1.0f) < 0.01f);

	// ��ȡ��ת�ǵ� sin cos
	float s, c;
	sinCos(&s, &c, theta);

	// ���� 1-cos(theta)��һЩ���õ��ӱ��ʽ
	float a = 1.0f - c;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;

	// ����Ԫ�ظ�ֵ
	m11 = ax * axis.x + c;
	m12 = ax * axis.y + axis.z * s;
	m13 = ax * axis.z - axis.y * s;

	m21 = ay * axis.x - axis.z * s;
	m22 = ay * axis.y + c;
	m23 = ay * axis.z + axis.x * s;

	m31 = az * axis.x + axis.y * s;
	m32 = az * axis.y - axis.x * s;
	m33 = az * axis.z + c;

	//ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//-------------------------------------------------------------------------------------------------------
// Matrix4x3::fromQuaternion
// ����Ԫ��ת��������
// ƽ�Ʋ�������

void Matrix4x3::fromQuaternion(const Quaternion& q)
{
	//����һЩ���õ��ӱ��ʽ
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	//����Ԫ�ظ�ֵ
	m11 = 1.0f - yy * q.y - zz * q.z;
	m12 = xx * q.y + ww * q.z;
	m13 = xx * q.z - ww * q.y;

	m21 = xx * q.y - ww * q.z;
	m22 = 1.0f - xx * q.x - zz * q.z;
	m23 = yy * q.z + ww * q.x;

	m31 = xx * q.z + ww * q.y;
	m32 = yy * q.z - ww * q.x;
	m33 = 1.0f - xx * q.x - yy * q.y;

	//ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//---------------------------------------------------------------------------------------
// Matrix4x3::setupScale
//
// �����ظ����������ŵľ���
// ������������kʹ������vector3(k,k,k) ��ʾ
//
// ƽ�Ʋ�������

void Matrix4x3::setupScale(const Vector3& s)
{
	// ����Ԫ�ظ�ֵ���ǳ�ֱ��
	m11 = s.x;  m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = s.y;  m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = s.z;

	//ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//------------------------------------------------------------------------------------------------------
// Matrix4x3::setupScaleAlongAxis
//
// ���������������ŵľ���
// ��ת��Ϊ��λ����
// ƽ�Ʋ�������

void Matrix4x3::setupScaleAlongAxis(const Vector3& axis, float k)
{
	// �����ת���Ƿ�Ϊ��λ����
	assert(fabs(axis * axis - 1.0f) < .01f);

	//����k-1�ͳ��õ��ӱ��ʽ
	float a = k - 1.0f;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;

	//����Ԫ�ظ�ֵ�����������Լ�����Ż���������Ϊ�Խ�Ԫ�����
	m11 = ax * axis.x + 1.0f;
	m22 = ay * axis.y + 1.0f;
	m33 = az * axis.z + 1.0f;

	m12 = m21 = ax * axis.y;
	m13 = m31 = ax * axis.z;
	m23 = m32 = ay * axis.z;

	//ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//-----------------------------------------------------------------------------------
// Matrix4x3::setupShear
// �����б����
// �б�������һ������ָ�����б�Ч������α������ʾ��
//
//	axis == 1 => y+= s*x, z+= t*x
//  axis == 2 => x+= s*y, z+= t*y
//  axis == 3 => x+= s*z, y+= t*z
// ƽ�Ʋ�������

void Matrix4x3::setupShear(int axis, float s, float t)
{
	//�ж��б�����
	switch (axis) {
	case 1: //��x�б�y��z
		m11 = 1.0f; m12 = s;    m13 = t;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	case 2: //��y�б�x��z
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = s;    m22 = 1.0f; m23 = t;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	case 3: //��z�б�x��y
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s;    m32 = t;    m33 = 1.0f;
		break;

	default:
		//�Ƿ�����
		assert(false);
	}

	// ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//-------------------------------------------------------------------------------------------------
// Matrix4x3::setupProject
// ����ͶӰ����ͶӰƽ���ԭ�㣬�Ҵ�ֱ�ڵ�λ����n

void Matrix4x3::setupProject(const Vector3& n)
{
	//�����ת���Ƿ�Ϊ��λ����
	assert(fabs(n * n - 1.0f) < 0.01f);

	//����Ԫ�ظ�ֵ�� ���������Լ�����Ż���������Ϊ��Խ�Ԫ�����
	m11 = 1.0f - n.x * n.x;
	m22 = 1.0f - n.y * n.y;
	m33 = 1.0f - n.z * n.z;

	m12 = m21 = -n.x * n.y;
	m13 = m31 = -n.x * n.y;
	m23 = m32 = -n.y * n.z;

	//ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//-----------------------------------------------------------------------------------------
// Matrix4x3::setupReflect
//
// ���췴��ƽ�棬����ƽ��ƽ��������ƽ��
//
// ����ƽ����һ������ָ��
//
// 1=> ��x= k ƽ�淴��
// 2=> ��y= k ƽ�淴��
// 3=> ��z= k ƽ�淴��
// 
// ƽ�Ʋ�����Ϊ���ʵ�ֵ����Ϊk��= 0 ʱƽ����һ���ᷢ����
//
// ���з���任��������ڲ���Ƭ�ᳯ�⣬���������޳�������Ӱ��

void Matrix4x3::setupReflect(int axis, float k)
{
	//�жϷ���ƽ��
	switch (axis) {

	case 1: //��x=k ƽ�淴��
		m11 = -1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f;  m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f; m33 = 1.0f;

		tx = 2.0f * k;
		ty = 0.0f;
		tz = 0.0f;

		break;

	case 2: //��y=k ƽ�淴��
		m11 = 1.0f;  m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = -1.0f; m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;

		tx = 0.0f;
		ty = 2.0f * k;
		tz = 0.0f;

		break;

	case 3: //��z=k ƽ�淴��
		m11 = 1.0f;  m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f;  m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f; m33 = -1.0f;

		tx = 0.0f;
		ty = 0.0f;
		tz = 2.0f * k;

		break;

	default:
		// �Ƿ�����
		assert(false);
	}
}

//--------------------------------------------------------------------------------------------------
// Matrix4x3::setupReflect
//
// ���췴����󣬷���ƽ��Ϊͨ��ԭ�������ƽ�棬�Ҵ�ֱ�ڵ�λ����n
// ƽ�Ʋ�������
//
// ���з���任��������ڲ���Ƭ�ᳯ�⣬���������޳�������Ӱ��

void Matrix4x3::setupReflect(const Vector3& n)
{
	//�����ת���Ƿ�Ϊ��λ����
	assert(fabs(n * n - 1.0f) < 0.01f);

	//���㹫���ӱ��ʽ
	float ax = -2.0f * n.x;
	float ay = -2.0f * n.y;
	float az = -2.0f * n.z;

	//����Ԫ�ظ�ֵ�����������Լ�����Ż���������Ϊ��Խ�Ԫ�����
	m11 = ax * n.x + 1.0f;
	m22 = ay * n.y + 1.0f;
	m33 = az * n.z + 1.0f;

	m12 = m21 = ax * n.y;
	m13 = m31 = ax * n.z;
	m23 = m32 = ay * n.z;

	//ƽ�Ʋ�������
	tx = ty = tz = 0.0f;
}

//----------------------------------------------------------------------------------------------
// matrix4x3 * vector
//
// �任�õ㣬��ʹ��ʹ�������������ֽ�������Դ���һ��ֱ��
//

Vector3 operator*(const Vector3& p, const Matrix4x3& m)
{
	//�������Դ�������
	return Vector3(
		p.x * m.m11 + p.y * m.m21 + p.z * m.m31,
		p.x * m.m12 + p.y * m.m22 + p.z * m.m32,
		p.x * m.m13 + p.y * m.m23 + p.z * m.m33
	);
}

//----------------------------------------------------------------------------------
// Matrix4x3 * Matrix4x3
//
// �������ˣ���ʹ��ʹ�þ����������ֽ�������Դ���һ��ֱ��
// �ṩ*=��������Է���c���Ե��﷨ϰ��
//

Matrix4x3 operator*(const Matrix4x3& a, const Matrix4x3& b)
{
	Matrix4x3 r;

	//��������3x3(���Ա任)����
	r.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	r.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	r.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;

	r.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	r.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	r.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;

	r.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	r.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	r.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;

	//����ƽ�Ʋ���
	r.tx = a.tx * b.m11 + a.ty * b.m21 + a.tz * b.m31 + b.tx;
	r.ty = a.tx * b.m12 + a.ty * b.m22 + a.tz * b.m32 + b.ty;
	r.tz = a.tx * b.m13 + a.ty * b.m23 + a.tz * b.m33 + b.tz;

	return r;
}

Vector3& operator*=(Vector3& p, const Matrix4x3& m)
{
	p = p * m;
	return p;
}

Matrix4x3& operator*=(Matrix4x3& a, const Matrix4x3& m)
{
	a = a * m;
	return a;
}

//--------------------------------------------------------------------------------------
// determinant
// �����������3x3���ֵ�����ʽ


float determinant(const Matrix4x3& m)
{
	return
		m.m11 * (m.m22 * m.m33 - m.m23 * m.m32)
		+ m.m12 * (m.m23 * m.m31 - m.m21 * m.m33)
		+ m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
}

//------------------------------------------------------------------------------------------------------
// inverse
//
// �������棬ʹ�þ���İ�������������ʽ�ķ���

Matrix4x3 inverse(const Matrix4x3& m)
{
	//��������ʽ
	float det = determinant(m);

	//���������ģ�������ʽΪ�㣬��û�������
	assert(fabsf(det) > 0.000001f);

	//����1/����ʽ����������ֻ��Ҫ��һ��
	float oneOverDet = 1.0f / det;

	//����3x3���ֵ��棬�ð�������������ʽ
	Matrix4x3 r;

	r.m11 = (m.m22 * m.m33 - m.m23 * m.m32) * oneOverDet;
	r.m12 = (m.m32 * m.m13 - m.m33 * m.m12) * oneOverDet; 
	r.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * oneOverDet;

	r.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * oneOverDet;  
	r.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * oneOverDet;
	r.m23 = (m.m21 * m.m13 - m.m11 * m.m23) * oneOverDet; 

	r.m31 = (m.m21 * m.m32 - m.m22 * m.m31) * oneOverDet;
	r.m32 = (m.m31 * m.m12 - m.m32 * m.m11) * oneOverDet;  
	r.m33 = (m.m11 * m.m22 - m.m12 * m.m21) * oneOverDet;

	// ����ƽ�Ʋ��ֵ���
	r.tx = -(m.tx * r.m11 + m.ty * r.m21 + m.tz * r.m31);
	r.ty = -(m.tx * r.m12 + m.ty * r.m22 + m.tz * r.m32);
	r.tz = -(m.tx * r.m13 + m.ty * r.m23 + m.tz * r.m33);

	//����ֵ�����ַ�����Ҫ���ÿ������캯��
	//����ٶȷǳ���Ҫ����Ҫ�õ����ĺ������ʵ��ĵط���������ֵ��
	return r;
}

//--------------------------------------------------------------------------------------------------
// getTranslation
//
// ����������ʽ����ƽ�Ʋ���

Vector3 getTranslation(const Matrix4x3& m)
{
	return Vector3(m.tx, m.ty, m.tz);
}

//--------------------------------------------------------------------------------------------------
// getPositionFromParentToLocalMatrix
//
// �Ӹ�->�ֲ��任��������ȡ����λ��
// �������������任

Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m)
{
	//����ƽ��ֵ����3x3���ֵ�ת��
	//���������������(�÷�������Ӧ���ڷǸ���任)
	return Vector3(
		-(m.tx * m.m11 + m.ty * m.m12 + m.tz * m.m13),
		-(m.tx * m.m21 + m.ty * m.m22 + m.tz * m.m23),
		-(m.tx * m.m31 + m.ty * m.m32 + m.tz * m.m33)
	);
}

//--------------------------------------------------------------------------------------------------
// getPositionFromLocalToParentMatrix
//
// �Ӿֲ�->��(������->����)�任��������ȡ�����λ��
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3& m)
{
	// ����Ҫ��λ�þ���ƽ�Ʋ���
	return Vector3(m.tx, m.ty, m.tz);
}
