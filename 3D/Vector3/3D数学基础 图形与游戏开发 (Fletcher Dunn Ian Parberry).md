# 3D数学基础 图形与游戏开发 (Fletcher Dunn Ian Parberry)

个人学习笔记。公式与 `Vector3/` 下的实现一一对应。

## 向量运算笔记

### 🔹 向量点乘 (Dot Product)

- **代数定义**

$a \cdot b = \sum_{i=1}^{n} a_i b_i$

- **几何定义**

$a \cdot b = \|a\| \, \|b\| \cos \theta$

点乘满足交换律、分配律；结果是一个标量。

------

### 🔹 向量叉乘 (Cross Product)（仅 3D 向量）

- **代数定义（行列式展开）**

$$
a \times b =
\begin{vmatrix}
\mathbf{i} & \mathbf{j} & \mathbf{k} \\
a_x & a_y & a_z \\
b_x & b_y & b_z
\end{vmatrix}
= (a_y b_z - a_z b_y)\mathbf{i} - (a_x b_z - a_z b_x)\mathbf{j} + (a_x b_y - a_y b_x)\mathbf{k}
$$

- **几何意义**

$\|a \times b\| = \|a\| \, \|b\| \sin \theta$

结果向量方向由 **右手定则** 确定，垂直于 $a$、$b$ 张成的平面。

存在 $b \times a = -(a \times b)$，即叉乘不满足交换律。

------

### 🔹 向量夹角 (Angle Between Vectors)

- **点乘法（无方向，范围 $[0, \pi]$）**

$\theta = \arccos \left( \dfrac{a \cdot b}{\|a\| \, \|b\|} \right)$

- **叉乘法（带方向，范围 $[-\pi/2, \pi/2]$）**

$\theta = \arcsin \left( \dfrac{\|a \times b\|}{\|a\| \, \|b\|} \right)$

实现上用 `safeAcos` 把入参夹到 $[-1, 1]$，避免浮点误差导致 `acos` 域非法。

------

### 🔹 向量的基本运算

- **长度 (Norm)**

$\|a\| = \sqrt{a_x^2 + a_y^2 + a_z^2}$

- **单位向量 (Normalization)**

$\hat{a} = \dfrac{a}{\|a\|}$

零向量归一化无意义，实现中先判断长度平方是否大于 0。

- **加减、数乘、数除** 均按分量运算：$(a \pm b)_i = a_i \pm b_i$，$(ka)_i = k a_i$。
- **距离**：$d(a,b) = \|a - b\|$。

------

### 🔹 三角函数基础

泰勒展开：

$\sin(x) \approx x - \dfrac{x^3}{3!} + \dfrac{x^5}{5!} - \dfrac{x^7}{7!} + \cdots$

$\cos(x) \approx 1 - \dfrac{x^2}{2!} + \dfrac{x^4}{4!} - \dfrac{x^6}{6!} + \cdots$

基本恒等式：

$\sin^2(x) + \cos^2(x) = 1$

------

## 矩阵

矩阵用**行向量右乘**约定：$p' = p \, M$，因此复合变换 $M = M_1 M_2$ 的乘法顺序与变换执行顺序一致。变换作用于物体时，是「物体坐标系 → 惯性坐标系」的坐标变换矩阵。

### 🔹 3D 旋转 — Rodrigues 公式

绕单位轴 $u$、角度 $\theta$ 旋转：

$$
R = I + \sin\theta \, [u]_\times + (1 - \cos\theta) \, [u]_\times^2
$$

其中 $[u]_\times$ 是叉乘的反对称矩阵。展开为具体 3×3 分量：

$$
R =
\begin{bmatrix}
(1-c)u_x^2 + c & (1-c)u_x u_y - s u_z & (1-c)u_x u_z + s u_y \\
(1-c)u_x u_y + s u_z & (1-c)u_y^2 + c & (1-c)u_y u_z - s u_x \\
(1-c)u_x u_z - s u_y & (1-c)u_y u_z + s u_x & (1-c)u_z^2 + c
\end{bmatrix}
$$

其中 $s = \sin\theta$，$c = \cos\theta$。

### 🔹 缩放

缩放矩阵是对角矩阵：

$$
S = \begin{bmatrix} s_x & 0 & 0 \\ 0 & s_y & 0 \\ 0 & 0 & s_z \end{bmatrix}
$$

沿任意轴 $n$（单位向量）缩放系数 $k$：$M = I + (k-1) n n^{\mathsf T}$。

### 🔹 切变 (Shear)

沿某轴切变，由两个切变系数 $s$、$t$ 描述。以沿 $y$ 轴切变为例：

$$
H = \begin{bmatrix} 1 & 0 & 0 \\ s & 1 & t \\ 0 & 0 & 1 \end{bmatrix}
$$

### 🔹 投影

向法线为 $n$ 的平面投影（垂直于 $n$ 投影掉）：

$P = I - n n^{\mathsf T}$

### 🔹 镜像 (Reflection)

沿法线 $n$ 的平面镜像：

$R = I - 2\, n n^{\mathsf T}$

沿坐标轴镜像则直接取反对应分量（如绕 $x = k$ 平面：$x' = 2k - x$）。

------

## 4×3 变换矩阵

用一个矩阵同时表达 **旋转 + 平移**。前 3×3 部分承载线性变换，第 4 行（列向量约定下是最后一列）承载平移：

$$
M =
\begin{bmatrix}
m_{11} & m_{12} & m_{13} \\
m_{21} & m_{22} & m_{23} \\
m_{31} & m_{32} & m_{33} \\
t_x & t_y & t_z
\end{bmatrix}
$$

点变换：$p' = p \, M + t$。

- **局部 → 父空间** / **父空间 → 局部**：由位置 `pos` 与朝向 `orient` 构造。
- 行列式取 3×3 部分；逆矩阵则先转置 3×3 部分，再对平移部分取负。

------

## 欧拉角

### 🔹 heading-pitch-bank 系统

| 角 | 含义 | 本笔记对应轴 |
|----|------|--------------|
| heading | 偏航 | $+y$ |
| pitch | 俯仰 | $+x$ |
| bank | 翻滚 | $+z$ |

### 🔹 规范化 (canonize)

同一朝向有无穷多种欧拉角表示。规范化把它收束到「限制」形式：

1. `pitch` 先 `wrapPi` 折到 $[-\pi, \pi]$；
2. 若 `pitch` 超出 $[-\pi/2, \pi/2]$，用等价表示翻回，同时给 `heading`、`bank` 各加 $\pi$；
3. `pitch` 处于 $\pm\pi/2$（万向锁）时，把全部旋转并入 `heading`，`bank` 置 0；
4. 其余情况对 `bank`、`heading` 分别 `wrapPi`。

### 🔹 wrapPi

$$
\text{wrapPi}(\theta) = \theta - 2\pi \left\lfloor \dfrac{\theta + \pi}{2\pi} \right\rfloor
$$

把任意角折到 $[-\pi, \pi]$。

------

## 四元数

### 🔹 定义

$q = [w, (x, y, z)] = w + x\mathbf{i} + y\mathbf{j} + z\mathbf{k}$

- 单位四元数：$\|q\| = \sqrt{w^2 + x^2 + y^2 + z^2} = 1$
- 「单位」四元数（无旋转）：$[1, (0,0,0)]$

### 🔹 绕轴旋转

绕单位轴 $n$、角度 $\theta$：

$q = \left[\cos\dfrac{\theta}{2},\ \sin\dfrac{\theta}{2}\, n\right]$

### 🔹 乘法

$$
q_1 q_2 = [\,w_1 w_2 - v_1 \cdot v_2,\ \ w_1 v_2 + w_2 v_1 + v_1 \times v_2\,]
$$

四元数乘法不满足交换律，且与矩阵乘法一样不满足。

### 🔹 共轭、模、逆

- 共轭：$q^* = [\,w, -v\,]$
- 模：$\|q\| = \sqrt{w^2 + \|v\|^2}$
- 逆：$q^{-1} = \dfrac{q^*}{\|q\|^2}$，单位四元数下 $q^{-1} = q^*$

用四元数旋转向量时，先构造旋转四元数的逆，再左乘、右乘：

$v' = q \, v \, q^{-1}$

（$v$ 写成标量部为 0 的四元数）。

### 🔹 球面线性插值 (slerp)

$$
\text{slerp}(p, q, t) = \frac{\sin\big((1-t)\omega\big)}{\sin\omega}\, p + \frac{\sin(t\omega)}{\sin\omega}\, q
$$

其中 $\cos\omega = p \cdot q$。插值前要检查点乘符号：若为负，取反其一，保证走「短弧」。

### 🔹 幂

$q^{t} = \left[\cos(t\omega),\ \sin(t\omega)\, n\right]$，其中 $\omega = \arccos(w)$，$n = \dfrac{v}{\|v\|}$。

------

## 各种旋转表示之间的转换

| 源 ↓ / 目标 → | 欧拉角 | 旋转矩阵 | 四元数 |
|---------------|--------|----------|--------|
| **欧拉角** | — | 由 $sh,ch,sp,cp,sb,cb$ 组合出 3×3 各元素 | 先转矩阵再转四元数 |
| **旋转矩阵** | $pitch = \arcsin(-m_{23})$，`heading`/`bank` 用 `atan2` 导出 | — | 用迹与对角线元素构造 |
| **四元数** | $pitch = \arcsin\!\big(-2(yz - wx)\big)$ 等；万向锁时退化为仅 `heading` | 由 $w,x,y,z$ 二次式直接写出 3×3 | — |

万向锁统一处理：当 $|\sin(pitch)| \to 1$ 时，`bank` 置 0，全部旋转并入 `heading`。

------

## 源码对照

| 文件 | 内容 |
|------|------|
| `Vector3.h/.cpp` | 向量、点乘、叉乘、归一化、距离、零向量常量 |
| `MathUtil.h/.cpp` | 圆周率常量、`wrapPi`、`safeAcos`、`sinCos` |
| `RotationMatrix.h/.cpp` | 3×3 旋转矩阵、欧拉角/四元数 → 矩阵、惯性↔物体变换 |
| `EulerAngles.h/.cpp` | heading-pitch-bank、`canonize`、四元数/矩阵 → 欧拉角 |
| `Quaternion.h/.cpp` | 四元数旋转、乘法、归一化、`slerp`、共轭、幂 |
| `Matrix4x3.h/.cpp` | 4×3 变换矩阵、平移/旋转/缩放/切变/投影/镜像、行列式与逆 |
