# 示例说明

每个示例都是独立可运行程序，构建与运行方式统一：

```bash
make dir=<目录名> run     # 在仓库根目录执行
```

除特别说明外，操作均为 `ESC` 退出；相机类示例（16 章起）额外支持 `W/A/S/D` 移动与鼠标拖动转向。

---

## 05_shader_class
演示把着色器编译链接封装成 `Shader` 类（`include/tools/shader.h`），并在此基础上绘制一个三角形。
- 输出：暗色背景上一个位于屏幕中心的三角形。

## 06_glsl_exercise
GLSL 练习：通过 `uniform` 传入水平偏移量，让三角形随时间左右往复移动。
- 输出：三角形沿 X 轴来回平移。

## 07_load_texture
用 `stb_image` 加载纹理，演示纹理坐标、环绕方式与过滤方式，并做纹理与顶点色的混合。
- 资源：`static/texture/container.jpg`、`awesomeface.png`。

## 08_texture_exercise
纹理练习：用 ImGui 滑块调节两个纹理的混合比例。
- 输出：木箱与笑脸纹理按比例叠加，滑块实时改变比例。

## 09_transform
用 `glm` 构造平移/旋转/缩放矩阵，让箱子随时间自转。
- 输出：单个纹理箱子绕 Z 轴持续旋转。

## 10_use_plane_geometry
使用自研 `PlaneGeometry`（`include/geometry/`）生成平面网格，替代手写顶点数组。
- 输出：贴图的平面。

## 11_use_sphere_geometry
使用自研 `SphereGeometry` 生成球体网格。
- 输出：贴图的球体。

## 12_use_box_geometry
使用自研 `BoxGeometry` 生成立方体网格。
- 输出：贴图的立方体。

## 13_model_view_projection
引入模型/视图/投影三个矩阵，把箱子、平面、球体放在统一的三维空间中并各自变换。
- 输出：透视投影下的三个物体，位置与姿态由 MVP 矩阵控制。

## 14_use_image_ui
使用 ImGui 显示帧率与滑块，并用 `ColorEdit3` 控制清屏颜色。
- 输出：左上角 ImGui 面板；控制台每帧打印滑块数值 `f = ...`。
- 交互：拖动 `float` 滑块 / 修改 `clear color`。

## 15_mvp_matrix_exercise
MVP 练习：用 ImGui 滑块实时调整物体位置、旋转与视场角。
- 输出：滑块变化即时反映到三个物体的变换上。

## 16_use_camera
手写相机：用键盘移动相机位置、鼠标控制朝向，构造观察矩阵与透视投影。
- 交互：`W/A/S/D` 移动，鼠标转向。

## 17_use_camera_class
把 16 章的相机逻辑封装为 `Camera` 类（`include/tools/camera.h`），实现自由飞行相机。
- 交互：`W/A/S/D` + 鼠标。

## 18_light_scene
搭建光照场景：物体着色器 + 光源立方体着色器，用不同颜色表示环境光/漫反射/镜面反射。
- 输出：一个被点光源照亮的箱子，以及一个表示光源位置的白色立方体。

## 19_basic_lighting
冯氏光照模型：环境光 + 漫反射 + 镜面反射，并加入距离衰减。
- 交互：`W/A/S/D` + 鼠标，可绕物体观察高光变化。

## 20_light_material
在光照计算中引入材质（环境光/漫反射/镜面反射分量与反光度 `shininess`）。
- 输出：可近观的高光衰减效果，展示材质与光照相乘的结果。

## 21_light_map
使用漫反射贴图与镜面反射贴图（光照贴图）替代单一材质颜色。
- 资源：`container2.png`、`container2_specular.png`。

## 22_light_map_exercise
光照贴图练习：额外采样一张带颜色的镜面反射贴图。
- 输出：金属边框区域呈现彩色高光。

## 23_direction_light
把光源抽象为平行光（定向光），用方向向量计算光照。
- 输出：光照方向固定，物体各处受光均匀。

## 24_point_light
点光源：光照方向由片段到光源的向量决定，并应用常数/一次/二次衰减项。
- 输出：移动光源时高光位置随之变化。

## 25_spot_light
聚光灯：在点光源基础上用 `cutOff` 与 `outerCutOff` 构造平滑边缘光锥。
- 输出：只有光锥范围内的物体被照亮，边缘柔和过渡。

## 26_multiple_lights
多光源：平行光 + 4 个点光源 + 聚光灯组合，统一在片段着色器里累加。
- 输出：多个彩色点光源同时照亮场景。

## 27_load_model
使用 assimp 加载 OBJ 模型（`include/tools/model.h` 的 `Model`/`Mesh`），递归处理节点与网格，并按材质加载纹理。
- 资源：默认 `static/model/nanosuit/nanosuit.obj`。
- 输出：带贴图与光照的纳米装模型。

## 28_depth_testing
深度测试：对比开启/关闭 `GL_DEPTH_TEST` 与 `glDepthFunc` 的效果，并演示 Z-fighting。
- 输出：两箱子与地板之间的前后遮挡关系正确。

## 29_stencil_testing
模板测试：用模板缓冲给物体描边，并演示对物体轮廓的放大绘制。
- 输出：箱子与地板带彩色描边。

## 30_blending
混合：绘制半透明窗户时按距离排序，演示 `glBlendFunc` 与丢弃全透明片段。
- 输出：透过半透明玻璃能看到后方场景。

## 31_face_culling
面剔除：通过顶点环绕顺序与 `glCullFace` 剔除背面。
- 输出：旋转箱子内部不会出现内表面；可切换剔除模式对比。

## 32_frame_buffers
帧缓冲：把场景先渲染到自定义帧缓冲的纹理上，再以反色/灰度/模糊效果绘制到屏幕。
- 输出：屏幕上的场景带有后期处理效果。

## 33_cube_maps
立方体贴图：加载 6 张面纹理构造天空盒。
- 输出：包围整个场景的立方体天空盒。

## 34_env_mapping
环境映射：用 `reflect` 做反射、`refract` 做折射，分别渲染两种材质。
- 输出：反射球与折射球，随相机移动呈现环境变化。

## 35_advanced_glsl
高级 GLSL：在着色器里直接读 `gl_VertexID`/`gl_FragCoord` 等内置变量，并用 uniform 缓冲对象（UBO）传递投影与视图矩阵。
- 输出：彩色方块阵列。

## 36_geometry_shader
几何着色器：动态生成法线可视化与爆破效果。
- 输出：可切换显示的法线线与图元爆炸动画。

## 37_instancing
实例化：一次绘制调用渲染 100 个位置随机的行星。
- 输出：大量行星分列成环。

## 37_instancing_rock
实例化进阶：加载小行星模型，用实例化矩阵数组把上万颗小行星一次性画到行星周围。
- 资源：`static/model/rock/rock.obj`、`planet/planet.obj`。

## 38_anti_aliasing
多重采样抗锯齿（MSAA）：创建多重采样帧缓冲并在其上渲染，用 ImGui 切换采样数。
- 输出：斜边锯齿明显减少。

## 39_blinn_phong
Blinn-Phong 光照：用半程向量替代反射向量计算镜面反射。
- 输出：高光比 Phong 更柔和，在低细分面上更自然。

## 40_gamma_corre
Gamma 校正：以 sRGB 空间加载纹理、在片段着色器做手动 gamma 校正，对比开启/关闭差异。
- 输出：开启校正后明暗过渡更自然。

## 41_shadow_mapping
阴影映射：从光源视角把深度渲染到深度贴图，再在片元里比较深度生成阴影。
- 输出：地板上的箱子投出硬阴影。

## 42_point_shadow
点光源阴影：用立方体贴图存 6 个方向的深度，实现全向阴影。
- 输出：点光源周围物体向各方向投射阴影。

## 43_normal_mapping
法线贴图：从贴图采样法线替换平面法线，让平面呈现凹凸细节。
- 资源：`brickwall_normal.jpg`。

## 43_normal_tangent
切线空间法线贴图：构造 TBN 矩阵，把切线空间的法线变换到世界空间。
- 输出：任意朝向的表面上凹凸细节方向均正确。

## 44_parallax_mapping
视差贴图：按高度图在切线空间偏移纹理坐标，制造视差立体感；用 `height_scale` 控制强度。
- 输出：砖墙表面随视角呈现真实凹凸位移。

## 45_heigh_dynamic_range
HDR：把场景渲染到浮点帧缓冲保存高动态范围颜色，再用曝光与色调映射转到屏幕。
- 交互：ImGui 中切换 HDR 开关并调节曝光。
- 资源：HDR 环境贴图与天空盒。

## 46_bloom
泛光：提取高亮区域做高斯模糊，再叠加回原场景。
- 交互：ImGui 调节泛光强度、模糊次数与 HDR 曝光。

## 47_deferred_shading
延迟着色：先渲染 G-buffer（位置/法线/颜色），再由光照阶段一次性计算大量光源。
- 输出：9 个金属球体，被 32 个随机颜色的点光源同时照亮，球面同时出现多组彩色高光与镜面反射。
