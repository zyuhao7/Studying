#include "EulerAngles.h"
#include "Quaternion.h"
#include "MathUtil.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"
#include <math.h>


// ȫ�֡���λ��ŷ���ǳ���
// �������ǻ���֪����������ȷ��ʱ������Ҫȡ������������ ����п����ڸö��󱻳�ʼ��֮ǰ��������������
// �ڴ����ʵ���У� �����ڳ���ʼʱ����ʼ����Ϊ0�� ���������������󱻹���֮ǰ��
// �任Ϊ "���Ƽ�" ŷ����

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);


//--------------------------------------------------------------
// EulerAngles::canonize
// ��ŷ����ת�������Ƽ���
// �ͱ�ʾ3D��Χ��Ŀ�Ķ��ԣ� ������ı�ŷ���ǵ�ֵ
// ������������ʾ��������ٶȵȣ�������Ӱ�졣

void EulerAngles::canonize()
{
	// ���Ƚ�pitch �任��-pi �� pi֮��
	pitch = wrapPi(pitch);

	// ���ڽ� pitch�任�� -pi/2 �� pi/2 ֮��
	if (pitch < -kPiOver2) {
		pitch = -kPi - pitch; 
		heading += kPi;
		bank += kPi;
	}
	else if (pitch > kPiOver2)
	{
		pitch = kPi - pitch;
		heading += kPi;
		bank += kPi;
	}

	// ���ڼ�������������������һ�������
	if (fabs(pitch) > kPiOver2 - 1e-4)
	{
		// ���������У� ���д�ֱ�����ת����heading
		heading += bank;
		bank = 0.0f;
	}
	else 
	{
		// ������������bankת�������Ƽ���
		bank = wrapPi(bank);
	}
	// ��headingת�������Ƽ���
	heading = wrapPi(heading);
}

//-----------------------------------------------------------------------
// EurlerAngles::fromWorldToObjectMatrix
// ������-��������ϵ�任����ŷ����
//
// ��������������ģ� ����ƽ�Ʋ���


//-------------------------------------------------------------------
// EulerAngles::fromObjectToInertialQuaternion
//
// ������-������Ԫ�� ��ŷ����

void EulerAngles::fromObjectToInertialQuternion(const Quaternion& q)
{
	// ���� sin(pitch)
	float sp = -2.0f * (q.y * q.z - q.w * q.x);

	// ������������������һ�����
	if (fabs(sp) > 0.99999f)
	{
		// ���Ϸ������·���
		pitch = kPiOver2 * sp;

		// bank ���㣬 ����heading
		heading = atan2f(q.w * q.y - q.x * q.z, 0.5f - q.y * q.y - q.z * q.z);
		bank = 0.0f;
	}
	else {

		// ����Ƕ�
		pitch = asinf(sp);
		heading = atan2f(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = atan2f(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}

}

//-----------------------------------------------------------------------
// EulerAngles::fromInertialToObjectQuaternion
//
// �ӹ���-������Ԫ�� ��ŷ����

void EulerAngles::fromInertialToObjectQuaternion(const Quaternion& q)
{
	// ���� sin(pitch)
	float sp = -2.0f * (q.y * q.z + q.w * q.x);

	// ������������������һ�����
	if (fabs(sp) > 0.99999f)
	{
		// ���Ϸ������·���
		pitch = kPiOver2 * sp;

		// bank ���㣬 ����heading
		heading = atan2f(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
		bank = 0.0f;
	}
	else {

		// ����Ƕ�
		pitch = asinf(sp);
		heading = atan2f(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = atan2f(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}
}

//----------------------------------------------------------------------
// EulerAngles::fromObjectToWorldMatrix
// ������-��������ϵ�任����ŷ����
// ��������������ģ�����ƽ�Ʋ���

void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3& m)
{
	//ͨ��m32����sin(pitch).
	float sp = -m.m32;

	//���������
	if (fabsf(sp) > 9.99999f)
	{

		// �����ϻ����·���
		pitch = kPiOver2 * sp;

		// bank ���㣬 ����heading
		heading = atan2f(-m.m13, m.m11);
		bank = 0.0f;
	}
	else
	{
		// ����Ƕ�
		heading = atan2f(m.m31, m.m33);
		pitch = asinf(sp);
		bank = atan2f(m.m12, m.m22);
	}
}

//-----------------------------------------------------------------------
// EurlerAngles::fromWorldToObjectMatrix
// ������-��������ϵ�任����ŷ����
// ��������������ģ� ����ƽ�Ʋ���

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3& m)
{
	// ����m23 ����sin(pitch)
	float sp = -m.m23;

	// ���������
	if (fabs(sp) > 9.99999f) {

		// ���Ϸ������·���
		pitch = kPiOver2 * sp;

		// bank ��0�� ����heading
		heading = atan2f(-m.m31, m.m11);
		bank = 0.0f;
	}
	else {

		// ����Ƕ�
		heading = atan2f(m.m13, m.m33);
		pitch = asinf(sp);
		bank = atan2f(m.m21, m.m22);
	}
}



//-------------------------------------------------------------------
// EulerAngles::fromRotationMatrix(const RotationMatrix &m)
// 
// ������ת������ŷ����

void EulerAngles::fromRotationMatrix(const RotationMatrix& m)
{
	// ����m23 ����sin(pitch)
	float sp = -m.m23;

	// ���������
	if (fabs(sp) > 9.99999f) {

		// ���Ϸ������·���
		pitch = kPiOver2 * sp;

		// bank ��0�� ����heading
		heading = atan2f(-m.m31, m.m11);
		bank = 0.0f;
	}
	else {

		// ����Ƕ�
		heading = atan2f(m.m13, m.m33);
		pitch = asinf(sp);
		bank = atan2f(m.m21, m.m22);
	}
}
