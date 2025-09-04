#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__
#include <math.h>
//////////////////////////////////////////////////////////////////////////////
// ������ѧ��ʽ
//////////////////////////////////////////////////////////////////////////////

// ����� pi �йصĳ���
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1Over2Pi = 1.0f / k2Pi;
// ͨ�������ʵ��� 2pi�����Ƕ������� -pi �� pi ��������
extern float wrapPi(float  theta);
//"��ȫ" �����Ǻ���
extern float safeAcos(float x);
// ����Ƕȵ� sin �� cos ֵ
inline void sinCos(float* returnSin, float* returnCos, float theta)
{
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

//////////////////////////////////////////////////////////////////////////////
#endif // !__MATHUTIL_H_INCLUDED__
