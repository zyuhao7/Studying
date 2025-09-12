#pragma once

class Vector3;
class EulerAngles;
class Quaternion;

//-------------------------------------------------------------------------------
// RotationMatrix ��
// ʵ����һ���򵥵�3x3 ���� ��������ת
// �������Ϊ�����ģ� �ڱ任ʱָ������

class RotationMatrix
{
public:
	// ��������
	//�����9��ֵ
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	//��������
	//��Ϊ��λ����
	void identity();

	//����ָ���ķ�λ�������
	void setup(const EulerAngles& orientation);

	// ������Ԫ��������󣬼������Ԫ����������ָ������ı任
	void fromInertialToObjectQuaternion(const Quaternion& q);
	void fromObjectToInertialQuaternion(const Quaternion& q);

	// ִ����ת
	Vector3 inertialToObject(const Vector3& v) const;
	Vector3 objectToInertial(const Vector3& v) const;
};

