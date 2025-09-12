#include "vector3.h"
#include "RotationMatrix.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "EulerAngles.h"

//////////////////////////////////////////////////////////////////////////////////////
//
// RotationMatrix 类
//
//-----------------------------------------------------------------------------------
//
//这个类的使用者应该很少需要关心矩阵的组织方式
//当然，对类的设计者来说应该使一切事情都显得非常直观
//假设矩阵仅为旋转矩阵，因此它是正交的
//该矩阵表达的是惯性到物体的变换，如果要执行物体到惯性的变换，应该乘以它的转置
//也就是说：
//
//惯性到物体的变换
//
//            |m11  m12  m13| |ix|   |ox|
//            |m21  m22  m23| |iy| = |oy|
//            |m31  m32  m33| |iz|   |oz|
//
//物体到惯性的变换
//
//            |m11  m21  m31| |ix|   |ox|
//            |m12  m22  m32| |iy| = |oy|
//            |m13  m23  m33| |iz|   |oz|
//
/////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------
//RotationMatrix::identity
//置为单位矩阵

void RotationMatrix::identity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

//---------------------------------------------------------------------------------------
//RoatationMatrix::setup
//用欧拉角参数构造矩阵

void RotationMatrix::setup(const EulerAngles& orientation)
{
	// 计算角度的 sin 和 cos 值
	float sh, ch, sb, cb, sp, cp;
	sinCos(&sh, &ch, orientation.heading);
	sinCos(&sb, &cb, orientation.bank);
	sinCos(&sp, &cp, orientation.pitch);

	// 填充矩阵
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
// 根据惯性-物体旋转四元数构造矩阵
//
void RotationMatrix::fromInertialToObjectQuaternion(const Quaternion& q)
{

	// 填充矩阵，还有优化的可能，因为许多子表达式是相同的， 我们把优化任务留给编译器。

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
// 根据物体-惯性旋转四元数构造矩阵
//
void RotationMatrix::fromObjectToInertialQuaternion(const Quaternion& q)
{
	// 填充矩阵，还有优化的可能，因为许多子表达式是相同的， 我们把优化任务留给编译器。
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
// 对向量做惯性-物体变换

Vector3 RotationMatrix::inertialToObject(const Vector3& v) const
{
	// 以 "标准" 方式执行矩阵乘法
	return Vector3(
		m11 * v.x + m21 * v.y + m31 * v.z,
		m12 * v.x + m22 * v.y + m32 * v.z,
		m13 * v.x + m23 * v.y + m33 * v.z
	);
}

//----------------------------------------------------------------------------------
// RotationMatrix::objectToInertial
//对向量做物体-惯性变换

Vector3 RotationMatrix::objectToInertial(const Vector3& v) const
{
	// 乘转置
	return Vector3(
		m11 * v.x + m12 * v.y + m13 * v.z,
		m21 * v.x + m22 * v.y + m23 * v.z,
		m31 * v.x + m32 * v.y + m33 * v.z
	);
}
