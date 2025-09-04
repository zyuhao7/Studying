#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__
#include <math.h>
//////////////////////////////////////////////////////////////////////////////
// 常用数学公式
//////////////////////////////////////////////////////////////////////////////

// 定义和 pi 有关的常量
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1Over2Pi = 1.0f / k2Pi;
// 通过增加适当的 2pi倍数角度限制在 -pi 到 pi 的区间中
extern float wrapPi(float  theta);
//"安全" 反三角函数
extern float safeAcos(float x);
// 计算角度的 sin 和 cos 值
inline void sinCos(float* returnSin, float* returnCos, float theta)
{
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

//////////////////////////////////////////////////////////////////////////////
#endif // !__MATHUTIL_H_INCLUDED__
