#include <math.h>
#include <assert.h>
#include "Quaternion.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"

////////////////////////////////////////////////////////
//
// 全局数据
//
////////////////////////////////////////////////////////
//全局单位四元数。注意Quaternion类没有构造函数，因为我们并不需要。
//因为Quaternion类是聚合类，所以可以使用 = {1.0f, 0.0f, 0.0f, 0.0f} 初始化。

const Quaternion kQuaternionIdentity = { 1.0f, 0.0f, 0.0f, 0.0f };



////////////////////////////////////////////////////////
//
// Quaternion 类成员
//
////////////////////////////////////////////////////////

//--------------------------------------------------------
// Quaternion::setToRotateAboutX
// Quaternion::setToRotateAboutY
// Quaternion::setToRotateAboutZ
// Quaternion::setToRotateAboutAxis

//构造绕指定轴旋转的四元数

void Quaternion::setToRotateAboutX(float theta)
{
	// 计算半角
	float thetaOver2 = theta * 0.5f;
	// 赋值
	w = cosf(thetaOver2);
	x = sinf(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
	// 计算半角
	float thetaOver2 = theta * 0.5f;
	// 赋值
	w = cosf(thetaOver2);
	x = 0.0f;
	y = sinf(thetaOver2);
	z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
	// 计算半角
	float thetaOver2 = theta * 0.5f;
	// 赋值
	w = cosf(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sinf(thetaOver2);
}

void Quaternion::setToRotateAboutAxis(const Vector3& axis, float theta)
{
	// 旋转轴必须标准化
	assert(fabs(vectorMag(axis) - 1.0f) < 0.01f);
	// 计算半角和sin值
	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sinf(thetaOver2);
	// 赋值
	w = cosf(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;

}

//----------------------------------------------------------
// Quaternion::setToRotateObjectToInertial
//构造物体-惯性旋转的四元数
//
//方位参数由欧拉角形式给出

void Quaternion::setToRotateObjectToInertial(const EulerAngles& orientation)
{
	// 计算半角的 sin和cos值
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);
	// 计算结果
	w = ch * cp * cb - sh * sp * sb;
	x = ch * sp * cb + sh * cp * sb;
	y = -ch * sp * sb + sh * cp * cb;
	z = -sh * sp * cb + ch * cp * sb;

}


//----------------------------------------------------------------------
//Quaternion::setToRotateInertialToObject
//
//构造执行惯性-物体旋转的四元数
//方位由欧拉角形式给出

void Quaternion::setToRotateInertialToObject(const EulerAngles& orientation)
{
	// 计算半角的sin和cos值
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);

	// 计算结果
	w = ch * cp * cb + sh * sp * sb;
	x = -ch * sp * cb - sh * cp * sb;
	y = ch * sp * sb - sh * cp * cb;
	z = sh * sp * cb - ch * cp * sb;
}

//------------------------------------------------------------------------------
// Quaternion::operator *
//
//四元数叉乘运算， 用以连接多个角位移
//乘的顺序是从左向右
//这和四元数叉乘的“标准”定义相反

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
// 叉乘并赋值，这是符合c++习惯的写法


Quaternion& Quaternion::operator*=(const Quaternion& a)
{
	*this = *this * a;
	return *this;
}

//--------------------------------------------------------------------------
// Quaternion::normalize
//
//正则化四元数
//通常，四元数都是正则化的
//
//提供这个函数主要是为了防止误差扩大，连续多个四元数操作可能导致误差扩大。
//

void Quaternion::normalize()
{
	// 计算四元数的模
	float mag = (float)sqrtf(w * w + x * x + y * y + z * z);
	// 检测长度, 防止除零错误
	if (mag > 0.0f)
	{
		// 正则化
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else
	{
		// 有麻烦了
		assert(false);
		// 在发布版本中, 返回单元四元数
		identity();
	}
}

//------------------------------------------------------------
// Quaternion::getRotationAngle
// 
//返回旋转角

float Quaternion::getRotationAngle() const
{
	// 计算半角, w = cos(theta / 2);
	float thetaOver2 = safeAcos(w);
	// 返回旋转角
	return thetaOver2 * 2.0f;
}

//-----------------------------------------------------------------
// Quaternion::getRotationAxis
//提取旋转轴

Vector3 Quaternion::getRotationAxis() const
{
	// 计算sin^2(theta/2), 记住 w = cos(theta/2). sin^2(x) + cos^2(x) = 1;
	float sinThetaOver2Sq = 1.0f - w * w;
	// 注意保证精确度
	if (sinThetaOver2Sq <= 0.0f)
	{
		// 单位四元数是不精确的数值, 只要返回有效的向量即可
		return Vector3(1.0f, 0.0f, 0.0f);
	}
	
	// 计算 1/sin(theta/2)
	float oneOverSinThetaOver2 = 1.0f / sqrtf(sinThetaOver2Sq);

	//返回旋转轴
	return Vector3(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
}


///////////////////////////////////////////////////////////////////////////////////////
//
// 非成员函数
//
///////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------
// dotProduct
// 四元数点乘
// 用非成员函数实现四元数点乘以避免在表达式中使用 "怪异的语法"

float dotProduct(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


//--------------------------------------------------------------------------------------
//slerp
//球面线性插值

Quaternion slerp(const Quaternion& p, const Quaternion& q, float t)
{
	// 检测出界的参数, 如果检测到, 返回边界点
	if (t <= 0.0f) return p;
	if (t >= 1.0f) return q;

	// 用点乘计算四元数夹角的 cos值
	float cosOmega = dotProduct(p, q);

	// 如果点乘为负, 使用 q
	// 四元数 q 和 -q 代表相同的旋转, 但可能产生不同的 slerp 运算, 因此要选正确的一个以便使用锐角进行旋转
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
	// 我们用的是两个单元四元数, 所以点乘结果应该 <= 1.0
	assert(cosOmega < 1.1f);

	// 计算插值片, 注意检查非常接近的情况
	float k0, k1;
	if (cosOmega > 0.99999f)
	{
		// 非常接近, 即线性插值, 防止除零
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		// 用三角公式sin^2(omega) + cos^2(omega) = 1 计算sin值
		float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);
		// 根据 sin 和 cos值 计算角度
		float omega = atan2f(sinOmega, cosOmega);
		// 计算分母的倒数, 这样只需要除一次
		float oneOverSinOmega = 1.0f / sinOmega;
		// 计算插值变量
		k0 = sinf((1.0f - t) * omega) * oneOverSinOmega;
		k1 = sinf(t * omega) * oneOverSinOmega;
	}
	// 插值
	Quaternion result;
	result.x = k0 * p.x + k1 * q.x;
	result.y = k0 * p.y + k1 * q.y;
	result.z = k0 * p.z + k1 * q.z;
	result.w = k0 * p.w + k1 * q.w;

	// 单位化
	result.normalize();
	// 返回
	return result;
}

//---------------------------------------------------------------------------
// conjugate
//
//四元数共轭，即与四元数旋转方向相反的四元数

Quaternion conjugate(const Quaternion& q)
{
	Quaternion result;
	// 旋转量相同
	result.w = q.w;

	// 旋转轴相反
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

//----------------------------------------------------------------------------
// pow
//
// 四元数幂

Quaternion pow(const Quaternion& q, float exponent)
{
	// 检查单位四元数, 防止除零
	if (fabs(q.w) > 0.99999f)
		return q;

	// 提取半角alpha(alpha = theta/2)
	float alpha = acosf(q.w);

	// 计算新 alpha 值
	float newAlpha = alpha * exponent;

	// 计算新w值
	Quaternion result;
	result.w = cosf(newAlpha);

	// 计算新 xyz 值
	float mult = sinf(newAlpha) / sinf(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;

	return result;
}
