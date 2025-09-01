# 3D数学基础 图形与游戏开发 (Fletcher Dunn Ian Parberry)

##  向量运算笔记

###🔹 向量点乘 (Dot Product)

- **代数定义**

$ \mathbf{a} \cdot \mathbf{b} = \sum_{i=1}^{n} a_i b_i $



- **几何定义**

$ \mathbf{a} \cdot \mathbf{b} = \|\mathbf{a}\| \, \|\mathbf{b}\| \cos \theta $



------

### 🔹 向量叉乘 (Cross Product) （仅 3D 向量）

- **代数定义（行列式展开）**

$ \mathbf{a} \times \mathbf{b} =
\begin{vmatrix}
\mathbf{i} & \mathbf{j} & \mathbf{k} \\
a_x & a_y & a_z \\
b_x & b_y & b_z
\end{vmatrix}
= (a_y b_z - a_z b_y)\mathbf{i} - (a_x b_z - a_z b_x)\mathbf{j} + (a_x b_y - a_y b_x)\mathbf{k} $



- **几何意义**

$ \|\mathbf{a} \times \mathbf{b}\| = \|\mathbf{a}\| \, \|\mathbf{b}\| \sin \theta $

结果向量方向由 **右手定则** 确定。



------

### 🔹 向量夹角 (Angle Between Vectors)

- **点乘法**

$ \theta = \arccos \left( \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{a}\| \, \|\mathbf{b}\|} \right) $



- **叉乘法（二维/三维可用，带方向）**

$ \theta = \arcsin \left( \frac{\|\mathbf{a} \times \mathbf{b}\|}{\|\mathbf{a}\| \, \|\mathbf{b}\|} \right) $



------

### 🔹 向量的基本运算

- **长度 (Norm)**

$ \|\mathbf{a}\| = \sqrt{a_x^2 + a_y^2 + a_z^2} $



- **单位向量 (Normalization)**

$ \hat{\mathbf{a}} = \frac{\mathbf{a}}{\|\mathbf{a}\|} $





![image-20250901155821302](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20250901155821302.png)

$ \sin(x) $

$ \cos(x) $



$\sin(x) \approx x - \frac{x^3}{3!} + \frac{x^5}{5!} - \frac{x^7}{7!} + \cdots$

$\cos(x) \approx 1 - \frac{x^2}{2!} + \frac{x^4}{4!} - \frac{x^6}{6!} + \cdots$



$\sin^2(x) + \cos^2(x) = 1$



$ \mathbf{a} \cdot \mathbf{b} = \|\mathbf{a}\| \, \|\mathbf{b}\| \cos \theta $

$ \theta = \arccos \left( \frac{\mathbf{a} \cdot \mathbf{b}}{\|\mathbf{a}\| \, \|\mathbf{b}\|} \right) $