#include "MathUtil.h"
#include "Vector3.h"

	
//-------------------------------------------------------------------------------------------
// 把任意角度（弧度制）规约到区间 [-π, π] 内
float wrapPi(float theta)
{
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

//-------------------------------------------------------------------------------------------
// safeAcos
// 和 acos(x) 相同, 但如果 x 超出范围将返回最为接近的有效值.
// 返回值在 0 到 pi 之间, 和 C 语言的 acos函数相同
float safeAcos(float x)
{
	if (x <= -1.0f) return kPi;
	if (x >= 1.0f) return 0.0f;
	return acos(x);
}

//-------------------------------------------------------------------------------------------

