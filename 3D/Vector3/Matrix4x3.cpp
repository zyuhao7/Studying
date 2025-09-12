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
// 本类的设计目的是为了便于使用， 用户不用反复改变正负号或者转置知道结果“看起来正确”，当然，内部实现的细节是很重要的
// 不仅是为了类的实现的正确性，也为了偶然可能发生的对矩阵元素的直接访问，或者为了优化
// 因此， 这里描述一下矩阵类所用的约定
//我们使用行向量，所以矩阵乘法形式如下：
//		      |m11 m12 m13|     
//			  |m21 m22 m23|   
// |x y z| *  |m31 m32 m33| = |x' y' z'|
//			  |tx  ty  tz |
//
//根据严格的线性代数法则，这种乘法是不成立的。
//我们可以假设，输入和输出向量有第四个分量，都为1
//另外，由于4x3矩阵是不能求逆的， 因此假设矩阵有第4列，为[0 0 0 1]
//如下所示：
//
//               |m11 m12 m13 0|   
//			     |m21 m22 m23 0|   
//   |x y z 1| * |m31 m32 m33 0| = |x' y' z' 1|
//               |tx  ty  tz  1|   
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Matrix4x3 类成员
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
// Matrix4x3::identity
// 置为单位矩阵

void Matrix4x3::identity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	tx = 0.0f; ty = 0.0f; tz = 0.0f;
}

//----------------------------------------------------------------------------------------------------
// Matrix4x3::zeroTranslation
//将包含平移部分的第四列置为零

void Matrix4x3::zeroTranslation()
{
	tx = ty = tz = 0.0f;
}

//----------------------------------------------------------------------------------------------------
// Matrix4x3::setTranslation
//平移部分赋值，参数为向量形式

void Matrix4x3::setTranslation(const Vector3& d)
{
	tx = d.x; ty = d.y; tz = d.z;
}

//----------------------------------------------------------------------------------------------------
// Matrix4x3::setupTranslation
//生成平移矩阵，参数为向量形式

void Matrix4x3::setupTranslation(const Vector3& d)
{
	//线性变换部分置为单位矩阵
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;

	// 平移部分赋值
	tx = d.x; ty = d.y; tz = d.z;
}

//----------------------------------------------------------------------------------------------
// Matrix4x3::setupLocalToParent
// 构造执行局部->父空间变换的矩阵，局部空间的位置和范围在父空间中描述
// 该方法最常见的用途是构造物体->世界的变换矩阵，这个变换是非常直接的。
// 首先从物体空间变换到惯性空间，接着变换到世界空间
// 方位可以由欧拉角后旋转矩阵指定

void Matrix4x3::setupLocalToParent(const Vector3& pos, const EulerAngles& orient)
{
	// 创建一个旋转矩阵
	RotationMatrix orientMatrix;
	orientMatrix.setup(orient); // 用欧拉角构造一个旋转矩阵

	// 构造4x3矩阵
	setupLocalToParent(pos, orientMatrix);

}

void Matrix4x3::setupLocalToParent(const Vector3& pos, const RotationMatrix& orient)
{
	// 复制矩阵的旋转部分
	//根据RotationMatrix 中的注释，旋转矩阵“一般”是惯性-物体矩阵
	//是父-局部关系
	//我们求的是局部-父关系的矩阵，因此要做转置
	m11 = orient.m11; m12 = orient.m21; m13 = orient.m31;
	m21 = orient.m12; m22 = orient.m22; m23 = orient.m32;
	m31 = orient.m13; m32 = orient.m23; m33 = orient.m33;

	// 现在设置平移部分, 平移在3x3部分之后, 因此我们只需简单复制其位置即可
	tx = pos.x; ty = pos.y; tz = pos.z;
}

//-------------------------------------------------------------------------------------------------
// Matrix4x3::setupParentToLocal
// 构造执行父-局部空间变换的矩阵，局部空间的位置和方位在父空间中描述
// 该方法最常见的用途是构造世界-物体的变换矩阵
// 通常这个变换首先从世界转换到惯性空间，接着转换到物体空间
// 4x3 矩阵可以完成后一个转换
// 所以我们想构造两个矩阵T和R，再连接M=TR
// 方位可以由欧拉角或旋转矩阵指定

void Matrix4x3::setupParentToLocal(const Vector3& pos, const EulerAngles& orient)
{
	// 创建一个旋转矩阵
	RotationMatrix orientMatrix;
	orientMatrix.setup(orient);

	// 构造 4x3 矩阵
	setupParentToLocal(pos, orientMatrix);
}

void Matrix4x3::setupParentToLocal(const Vector3& pos, const RotationMatrix& orient)
{
	// 复制矩阵的旋转部分
	// 可以直接复制元素
	m11 = orient.m11; m12 = orient.m12; m13 = orient.m13;
	m21 = orient.m21; m22 = orient.m22; m23 = orient.m23;
	m31 = orient.m31; m32 = orient.m32; m33 = orient.m33;

	// 设置平移部分
	// 一般来说，从世界空间到惯性空间只需要平移负的量
	// 但必须记得旋转是“先”发生的，所以应该旋转平移部分
	// 这和先创建平移-pos的矩阵，再创建旋转矩阵R，
	// 再把它们连接成TR是一样的
	tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
	ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
	tz = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
}

//------------------------------------------------------------------------------------------
// Matrix4x3::setupRotate
// 构造绕坐标轴旋转的矩阵
// 旋转轴从1开始索引指定
//
// 1 => 绕x轴旋转
// 2 => 绕y轴旋转
// 3 => 绕z轴旋转
// theta 是旋转量，以弧度表示，用右手法则定义“正方向”
//	平移部分置零

void Matrix4x3::setupRotate(int axis, float theta)
{
	// 取得旋转角的 cos 和 sin 值
	float s, c;
	sinCos(&s, &c, theta);

	// 判断旋转轴
	switch (axis)
	{
	case 1: // 绕 x 轴旋转
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c; m23 = s;
		m31 = 0.0f; m32 = -s; m33 = c;
		break;

	case 2: // 绕 y 轴旋转
		m11 = c; m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = 0.0f; m33 = c;
		break;

	case 3: // 绕 z 轴旋转
		m11 = c; m12 = s; m13 = 0.0f;
		m21 = -s; m22 = c; m23 = 0;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	default:
		//非法索引
		assert(false);
	}

	tx = ty = tz = 0.0f;
}

//-------------------------------------------------------------------------------------------------------
// Matrix4x3::setupRotate
// 构造绕任意轴旋转，任意轴通过原点
// 旋转轴为单位向量
// theta 是旋转向量，以弧度表示，用左手法则来定义"正方向"
// 平移部分置零

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
	// TODO: 在此处插入 return 语句
}

Matrix4x3& operator*=(Matrix4x3& a, const Matrix4x3& m)
{
	// TODO: 在此处插入 return 语句
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
