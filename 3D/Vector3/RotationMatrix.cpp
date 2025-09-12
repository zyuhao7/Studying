#include "vector3.h"
#include "RotationMatrix.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "EulerAngles.h"

//////////////////////////////////////////////////////////////////////////////////////
//
// RotationMatrix ��
//
//-----------------------------------------------------------------------------------
//
//������ʹ����Ӧ�ú�����Ҫ���ľ������֯��ʽ
//��Ȼ��������������˵Ӧ��ʹһ�����鶼�Ե÷ǳ�ֱ��
//��������Ϊ��ת�����������������
//�þ�������ǹ��Ե�����ı任�����Ҫִ�����嵽���Եı任��Ӧ�ó�������ת��
//Ҳ����˵��
//
//���Ե�����ı任
//
//            |m11  m12  m13| |ix|   |ox|
//            |m21  m22  m23| |iy| = |oy|
//            |m31  m32  m33| |iz|   |oz|
//
//���嵽���Եı任
//
//            |m11  m21  m31| |ix|   |ox|
//            |m12  m22  m32| |iy| = |oy|
//            |m13  m23  m33| |iz|   |oz|
//
/////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------
//RotationMatrix::identity
//��Ϊ��λ����

void RotationMatrix::identity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

//---------------------------------------------------------------------------------------
//RoatationMatrix::setup
//��ŷ���ǲ����������

void RotationMatrix::setup(const EulerAngles& orientation)
{
	// ����Ƕȵ� sin �� cos ֵ
	float sh, ch, sb, cb, sp, cp;
	sinCos(&sh, &ch, orientation.heading);
	sinCos(&sb, &cb, orientation.bank);
	sinCos(&sp, &cp, orientation.pitch);

	// ������
	m11 = ch * cb + sh * sp * sb;
	m12 = cp * sb;
	m13 = -sh * cb + ch * sp * sb;

	m21 = -ch * sb + sh * sp * cb;
	m22 = cp * cb;
	m23 = sh * sb + ch * sp * cb;

	m31 = sh * cp;
	m32 = -sp;
	m33 = ch * cp;
}

//--------------------------------------------------------------------------------
// RotationMatrix::fromInertialToObjectQuaternion
// ���ݹ���-������ת��Ԫ���������
//
void RotationMatrix::fromInertialToObjectQuaternion(const Quaternion& q)
{

	// �����󣬻����Ż��Ŀ��ܣ���Ϊ����ӱ��ʽ����ͬ�ģ� ���ǰ��Ż�����������������

	m11 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	m12 = 2.0f * (q.x * q.y + q.w * q.z);
	m13 = 2.0f * (q.x * q.z - q.w * q.y);

	m21 = 2.0f * (q.x * q.y - q.w * q.z);
	m22 = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
	m23 = 2.0f * (q.y * q.z + q.w * q.x);

	m31 = 2.0f * (q.x * q.z + q.w * q.y);
	m32 = 2.0f * (q.y * q.z - q.w * q.x);
	m33 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);

}

//------------------------------------------------------------------------------------------------
// RotationMatrix::fromObjectToInertialQuaternion
// ��������-������ת��Ԫ���������
//
void RotationMatrix::fromObjectToInertialQuaternion(const Quaternion& q)
{
	// �����󣬻����Ż��Ŀ��ܣ���Ϊ����ӱ��ʽ����ͬ�ģ� ���ǰ��Ż�����������������
	m11 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
	m12 = 2.0f * (q.x * q.y - q.w * q.z);
	m13 = 2.0f * (q.x * q.z + q.w * q.y);

	m21 = 2.0f * (q.x * q.y + q.w * q.z);
	m22 = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
	m23 = 2.0f * (q.y * q.z - q.w * q.x);

	m31 = 2.0f * (q.x * q.z - q.w * q.y);
	m32 = 2.0f * (q.y * q.z + q.w * q.x);
	m33 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
}

//------------------------------------------------------------------------------
//RotationMatrix::inertialToObject
// ������������-����任

Vector3 RotationMatrix::inertialToObject(const Vector3& v) const
{
	// �� "��׼" ��ʽִ�о���˷�
	return Vector3(
		m11 * v.x + m21 * v.y + m31 * v.z,
		m12 * v.x + m22 * v.y + m32 * v.z,
		m13 * v.x + m23 * v.y + m33 * v.z
	);
}

//----------------------------------------------------------------------------------
// RotationMatrix::objectToInertial
//������������-���Ա任

Vector3 RotationMatrix::objectToInertial(const Vector3& v) const
{
	// ��ת��
	return Vector3(
		m11 * v.x + m12 * v.y + m13 * v.z,
		m21 * v.x + m22 * v.y + m23 * v.z,
		m31 * v.x + m32 * v.y + m33 * v.z
	);
}
