// main.cpp —— 3D 数学基础 演示驱动
// 逐个演示 Vector3 / 欧拉角 / 旋转矩阵 / 四元数 / 4x3 变换矩阵 的用法。
// 构建：cmake -S . -B build && cmake --build build && ./build/demo

#include <iostream>
#include <iomanip>

#include "Vector3.h"
#include "MathUtil.h"
#include "EulerAngles.h"
#include "RotationMatrix.h"
#include "Quaternion.h"
#include "Matrix4x3.h"

using namespace std;

static void section(const char* title)
{
	cout << "\n========== " << title << " ==========\n";
}

static void printV(const char* label, const Vector3& v)
{
	cout << label << " = (" << v.x << ", " << v.y << ", " << v.z << ")\n";
}

static void printQ(const char* label, const Quaternion& q)
{
	cout << label << " = [w=" << q.w << ", x=" << q.x
		<< ", y=" << q.y << ", z=" << q.z << "]\n";
}

int main()
{
	cout << fixed << setprecision(4);

	// ---------------------------------------------------------------
	section("Vector3 基本运算");
	Vector3 a(1.0f, 2.0f, 3.0f);
	Vector3 b(4.0f, 5.0f, 6.0f);
	printV("a", a);
	printV("b", b);
	cout << "a . b            = " << a * b << "\n";
	printV("a x b", crossProduct(a, b));
	printV("a + b", a + b);
	printV("-a", -a);
	printV("a * 2", a * 2.0f);
	cout << "|a|              = " << vectorMag(a) << "\n";
	cout << "distance(a, b)   = " << distance(a, b) << "\n";
	Vector3 n = a;
	n.normalize();
	printV("normalize(a)", n);
	cout << "|normalize(a)|   = " << vectorMag(n) << "\n";

	// ---------------------------------------------------------------
	section("欧拉角 -> 旋转矩阵");
	EulerAngles orient(0.0f, 0.0f, kPiOver2); // bank = 90 度
	cout << "heading=" << orient.heading
		<< " pitch=" << orient.pitch
		<< " bank=" << orient.bank << "\n";
	RotationMatrix rm;
	rm.setup(orient);
	Vector3 xAxis(1.0f, 0.0f, 0.0f);
	printV("objectToInertial(1,0,0)", rm.objectToInertial(xAxis));
	printV("inertialToObject(1,0,0)", rm.inertialToObject(xAxis));

	// ---------------------------------------------------------------
	section("四元数");
	Quaternion qz;
	qz.setToRotateAboutZ(kPiOver2);
	printQ("绕 Z 轴 90 度", qz);
	cout << "旋转角 = " << qz.getRotationAngle() << " 弧度\n";
	printV("旋转轴", qz.getRotationAxis());

	Quaternion qx;
	qx.setToRotateAboutX(kPiOver2);
	printQ("绕 X 轴 90 度", qx);
	printQ("qz * qx", qz * qx);
	printQ("qx * qz", qx * qz);
	cout << "(两者不同 -> 四元数乘法不可交换)\n";

	Quaternion qi;
	qi.identity();
	Quaternion half = slerp(qi, qz, 0.5f);
	printQ("slerp(identity, qz, 0.5)", half);
	cout << "插值后旋转角 = " << half.getRotationAngle()
		<< " 弧度 (期望 " << kPiOver2 * 0.5f << ")\n";

	printQ("conjugate(qz)", conjugate(qz));

	// ---------------------------------------------------------------
	section("4x3 变换矩阵");
	Matrix4x3 trans;
	trans.setupTranslation(Vector3(1.0f, 2.0f, 3.0f));
	printV("平移部分", getTranslation(trans));
	printV("(10,0,0) * 平移矩阵", Vector3(10.0f, 0.0f, 0.0f) * trans);

	Matrix4x3 rot;
	rot.setupRotate(Vector3(0.0f, 0.0f, 1.0f), kPiOver2);
	printV("(1,0,0) * 绕Z旋转90", Vector3(1.0f, 0.0f, 0.0f) * rot);

	Matrix4x3 comp = rot * trans; // 先旋转, 后平移
	printV("(1,0,0) * (rot * trans)", Vector3(1.0f, 0.0f, 0.0f) * comp);

	cout << "det(rot) = " << determinant(rot) << "\n";

	Matrix4x3 inv = inverse(comp);
	Vector3 p(3.0f, -4.0f, 5.0f);
	printV("p", p);
	printV("p * comp * inverse(comp)", p * comp * inv);

	return 0;
}
