#include <math.h>
#include <assert.h>
#include "Quaternion.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"

////////////////////////////////////////////////////////
//
// ȫ������
//
////////////////////////////////////////////////////////
//ȫ�ֵ�λ��Ԫ����ע��Quaternion��û�й��캯������Ϊ���ǲ�����Ҫ��
//��ΪQuaternion���Ǿۺ��࣬���Կ���ʹ�� = {1.0f, 0.0f, 0.0f, 0.0f} ��ʼ����

const Quaternion kQuaternionIdentity = { 1.0f, 0.0f, 0.0f, 0.0f };



////////////////////////////////////////////////////////
//
// Quaternion ���Ա
//
////////////////////////////////////////////////////////

//--------------------------------------------------------
// Quaternion::setToRotateAboutX
// Quaternion::setToRotateAboutY
// Quaternion::setToRotateAboutZ
// Quaternion::setToRotateAboutAxis

//������ָ������ת����Ԫ��

void Quaternion::setToRotateAboutX(float theta)
{
	// ������
	float thetaOver2 = theta * 0.5f;
	// ��ֵ
	w = cosf(thetaOver2);
	x = sinf(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
	// ������
	float thetaOver2 = theta * 0.5f;
	// ��ֵ
	w = cosf(thetaOver2);
	x = 0.0f;
	y = sinf(thetaOver2);
	z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
	// ������
	float thetaOver2 = theta * 0.5f;
	// ��ֵ
	w = cosf(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sinf(thetaOver2);
}

void Quaternion::setToRotateAboutAxis(const Vector3& axis, float theta)
{
	// ��ת������׼��
	assert(fabs(vectorMag(axis) - 1.0f) < 0.01f);
	// �����Ǻ�sinֵ
	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sinf(thetaOver2);
	// ��ֵ
	w = cosf(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;

}

//----------------------------------------------------------
// Quaternion::setToRotateObjectToInertial
//��������-������ת����Ԫ��
//
//��λ������ŷ������ʽ����

void Quaternion::setToRotateObjectToInertial(const EulerAngles& orientation)
{
	// �����ǵ� sin��cosֵ
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);
	// ������
	w = ch * cp * cb - sh * sp * sb;
	x = ch * sp * cb + sh * cp * sb;
	y = -ch * sp * sb + sh * cp * cb;
	z = -sh * sp * cb + ch * cp * sb;

}


//----------------------------------------------------------------------
//Quaternion::setToRotateInertialToObject
//
//����ִ�й���-������ת����Ԫ��
//��λ��ŷ������ʽ����

void Quaternion::setToRotateInertialToObject(const EulerAngles& orientation)
{
	// �����ǵ�sin��cosֵ
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);

	// ������
	w = ch * cp * cb + sh * sp * sb;
	x = -ch * sp * cb - sh * cp * sb;
	y = ch * sp * sb - sh * cp * cb;
	z = sh * sp * cb - ch * cp * sb;
}

//------------------------------------------------------------------------------
// Quaternion::operator *
//
//��Ԫ��������㣬 �������Ӷ����λ��
//�˵�˳���Ǵ�������
//�����Ԫ����˵ġ���׼�������෴

Quaternion Quaternion::operator*(const Quaternion& a) const
{
	Quaternion result;

	result.w = w * a.w - x * a.x - y * a.y - z * a.z;
	result.x = w * a.x + x * a.w + z * a.y - y * a.z;
	result.y = w * a.y + y * a.w + x * a.z - z * a.x;
	result.z = w * a.z + z * a.w + y * a.x - x * a.y;

	return result;
}

//------------------------------------------------------------------------------
// Quaternion::operator*=
//
// ��˲���ֵ�����Ƿ���c++ϰ�ߵ�д��


Quaternion& Quaternion::operator*=(const Quaternion& a)
{
	*this = *this * a;
	return *this;
}

//--------------------------------------------------------------------------
// Quaternion::normalize
//
//������Ԫ��
//ͨ������Ԫ���������򻯵�
//
//�ṩ���������Ҫ��Ϊ�˷�ֹ����������������Ԫ���������ܵ����������
//

void Quaternion::normalize()
{
	// ������Ԫ����ģ
	float mag = (float)sqrtf(w * w + x * x + y * y + z * z);
	// ��ⳤ��, ��ֹ�������
	if (mag > 0.0f)
	{
		// ����
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else
	{
		// ���鷳��
		assert(false);
		// �ڷ����汾��, ���ص�Ԫ��Ԫ��
		identity();
	}
}

//------------------------------------------------------------
// Quaternion::getRotationAngle
// 
//������ת��

float Quaternion::getRotationAngle() const
{
	// ������, w = cos(theta / 2);
	float thetaOver2 = safeAcos(w);
	// ������ת��
	return thetaOver2 * 2.0f;
}

//-----------------------------------------------------------------
// Quaternion::getRotationAxis
//��ȡ��ת��

Vector3 Quaternion::getRotationAxis() const
{
	// ����sin^2(theta/2), ��ס w = cos(theta/2). sin^2(x) + cos^2(x) = 1;
	float sinThetaOver2Sq = 1.0f - w * w;
	// ע�Ᵽ֤��ȷ��
	if (sinThetaOver2Sq <= 0.0f)
	{
		// ��λ��Ԫ���ǲ���ȷ����ֵ, ֻҪ������Ч����������
		return Vector3(1.0f, 0.0f, 0.0f);
	}
	
	// ���� 1/sin(theta/2)
	float oneOverSinThetaOver2 = 1.0f / sqrtf(sinThetaOver2Sq);

	//������ת��
	return Vector3(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
}


///////////////////////////////////////////////////////////////////////////////////////
//
// �ǳ�Ա����
//
///////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------
// dotProduct
// ��Ԫ�����
// �÷ǳ�Ա����ʵ����Ԫ������Ա����ڱ��ʽ��ʹ�� "������﷨"

float dotProduct(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


//--------------------------------------------------------------------------------------
//slerp
//�������Բ�ֵ

Quaternion slerp(const Quaternion& p, const Quaternion& q, float t)
{
	// ������Ĳ���, �����⵽, ���ر߽��
	if (t <= 0.0f) return p;
	if (t >= 1.0f) return q;

	// �õ�˼�����Ԫ���нǵ� cosֵ
	float cosOmega = dotProduct(p, q);

	// ������Ϊ��, ʹ�� q
	// ��Ԫ�� q �� -q ������ͬ����ת, �����ܲ�����ͬ�� slerp ����, ���Ҫѡ��ȷ��һ���Ա�ʹ����ǽ�����ת
	float qw = q.w;
	float qx = q.x;
	float qy = q.y;
	float qz = q.z;
	if (cosOmega < 0.0f)
	{
		qw = -q.w;
		qx = -q.x;
		qy = -q.y;
		qz = -q.z;
		cosOmega = -cosOmega;
	}
	// �����õ���������Ԫ��Ԫ��, ���Ե�˽��Ӧ�� <= 1.0
	assert(cosOmega < 1.1f);

	// �����ֵƬ, ע����ǳ��ӽ������
	float k0, k1;
	if (cosOmega > 0.99999f)
	{
		// �ǳ��ӽ�, �����Բ�ֵ, ��ֹ����
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		// �����ǹ�ʽsin^2(omega) + cos^2(omega) = 1 ����sinֵ
		float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
		// ���� sin �� cosֵ ����Ƕ�
		float omega = atan2f(sinOmega, cosOmega);
		// �����ĸ�ĵ���, ����ֻ��Ҫ��һ��
		float oneOverSinOmega = 1.0f / sinOmega;
		// �����ֵ����
		k0 = sinf((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sinf(t * omega) * oneOverSinOmega;
	}
	// ��ֵ
	Quaternion result;
	result.x = k0 * p.x + k1 * q.x;
	result.y = k0 * p.y + k1 * q.y;
	result.z = k0 * p.z + k1 * q.z;
	result.w = k0 * p.w + k1 * q.w;

	// ��λ��
	result.normalize();
	// ����
	return result;
}

//---------------------------------------------------------------------------
// conjugate
//
//��Ԫ�����������Ԫ����ת�����෴����Ԫ��

Quaternion conjugate(const Quaternion& q)
{
	Quaternion result;
	// ��ת����ͬ
	result.w = q.w;

	// ��ת���෴
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

//----------------------------------------------------------------------------
// pow
//
// ��Ԫ����

Quaternion pow(const Quaternion& q, float exponent)
{
	// ��鵥λ��Ԫ��, ��ֹ����
	if (fabs(q.w) > 0.99999f)
		return q;

	// ��ȡ���alpha(alpha = theta/2)
	float alpha = acosf(q.w);

	// ������ alpha ֵ
	float newAlpha = alpha * exponent;

	// ������wֵ
	Quaternion result;
	result.w = cosf(newAlpha);

	// ������ xyz ֵ
	float mult = sinf(newAlpha) / sinf(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;

	return result;
}
