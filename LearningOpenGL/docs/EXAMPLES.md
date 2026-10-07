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

---

# 官方移植示例

以下目录从官方 [LearnOpenGL 仓库](https://github.com/JoeyDeVries/LearnOpenGL) 移植，目录名与官方编号一致，构建方式同上。

依赖方面：官方仓库的 `8.guest`、`7.in_practice/2.text_rendering`、`7.in_practice/3.2d_game` 需要 irrKlang 音频或 freetype 文本渲染，未移植；官方各章的"练习"目录（如 `3.4.shaders_exercise1`、`2.3.basic_lighting_exercise1`）只给出 GLSL 片段或留白，不是完整程序，也未移植。此外官方 `5.advanced_lighting/3.3.csm` 目录内容其实是深度可视化示例的副本（引用了不存在的 `depth_testing.vs`），不在官方 `CMakeLists.txt` 的构建列表里，同样未移植；真正的级联阴影映射在官方 guest 章节。

## 1.getting_started

| 示例 | 内容 |
| --- | --- |
| `1.1.hello_window` | 创建 GLFW 窗口与 OpenGL 4.6 core 上下文，跑事件循环。 |
| `1.2.hello_window_clear` | 在上一例基础上加 `glClearColor` 与双缓冲交换。 |
| `2.1.hello_triangle` | 最小三角形：VBO/VAO + 顶点/片段着色器。 |
| `2.2.hello_triangle_indexed` | 用 EBO（索引缓冲）画四边形。 |
| `2.3.hello_triangle_exercise1` | 练习：给三个顶点加不同颜色。 |
| `2.4.hello_triangle_exercise2` | 练习：用两个 VAO/VBO 画两个相邻三角形。 |
| `2.5.hello_triangle_exercise3` | 练习：同一 VBO 配两个 VAO，用各自着色器渲染。 |
| `3.1.shaders_uniform` | 通过 `uniform` 传入颜色，让三角形颜色随时间变化。 |
| `3.2.shaders_interpolation` | 顶点属性输出插值到片段着色器，呈现渐变色三角形。 |
| `3.3.shaders_class` | 把着色器编译链接封装成类，在显存中存多个 VAO。 |
| `4.1.textures` | 加载纹理贴到三角形上（stb_image）。 |
| `4.2.textures_combined` | 两张纹理按比例混合（木箱 + 笑脸）。 |
| `4.4.textures_exercise2` | 练习：交换两张纹理的混合比例。 |
| `4.5.textures_exercise3` | 练习：用方向键增减混合比例。 |
| `4.6.textures_exercise4` | 练习：用 `S` 键循环翻转纹理。 |
| `5.1.transformations` | 用 GLM 构造变换矩阵，让箱子自转。 |
| `5.2.transformations_exercise2` | 练习：在旋转箱子的同时加一层随时间变化的平移。 |
| `6.1.coordinate_systems` | 引入模型/视图/投影矩阵，把箱子放到三维空间。 |
| `6.2.coordinate_systems_depth` | 打开深度测试，多放几个箱子并正确处理前后遮挡。 |
| `6.3.coordinate_systems_multiple` | 用循环渲染 10 个不同位置的箱子。 |
| `7.1.camera_circle` | 相机绕原点做圆周运动，看向场景中心。 |
| `7.2.camera_keyboard_dt` | 用 `W/A/S/D` 移动相机，并按帧间隔 `deltaTime` 归一化速度。 |
| `7.3.camera_mouse_zoom` | 鼠标拖动转向、滚轮缩放（FOV）。 |
| `7.4.camera_class` | 把相机封装成类，实现自由飞行相机。 |

## 2.lighting

| 示例 | 内容 |
| --- | --- |
| `1.colors` | 物体颜色与光源颜色相乘，并显示一个表示光源位置的立方体。 |
| `2.1.basic_lighting_diffuse` | 法线 + 光源方向计算漫反射。 |
| `2.2.basic_lighting_specular` | 加上镜面反射（反射向量与视线夹角）。 |
| `3.1.materials` | 引入材质（环境/漫反射/镜面分量与 `shininess`）。 |
| `3.2.materials_exercise1` | 练习：让光源随时间绕物体旋转。 |
| `4.1.lighting_maps_diffuse_map` | 用漫反射贴图替代单一材质颜色。 |
| `4.2.lighting_maps_specular_map` | 再加镜面反射贴图，金属边框呈现高光。 |
| `4.4.lighting_maps_exercise4` | 练习：让镜面贴图带上颜色。 |
| `5.1.light_casters_directional` | 平行光（定向光），光照方向固定。 |
| `5.2.light_casters_point` | 点光源，含常数/一次/二次衰减项。 |
| `5.3.light_casters_spot` | 聚光灯，用 `cutOff`/`outerCutOff` 做平滑光锥。 |
| `5.4.light_casters_spot_soft` | 用内/外锥角插值得到软化边缘的聚光灯。 |
| `6.multiple_lights` | 平行光 + 4 个点光源 + 聚光灯统一累加。 |

## 3.model_loading

| 示例 | 内容 |
| --- | --- |
| `1.model_loading` | 用 assimp 加载 OBJ，递归处理节点与网格并加载材质纹理。 |

## 4.advanced_opengl

| 示例 | 内容 |
| --- | --- |
| `1.1.depth_testing` | 对比 `GL_DEPTH_TEST` 开关与 `glDepthFunc` 的效果。 |
| `1.2.depth_testing_view` | 用 `gl_FragCoord.z` 可视化深度值，并用 `Z` 键切换。 |
| `2.stencil_testing` | 模板测试给物体描出彩色边框。 |
| `3.1.blending_discard` | 用 `discard` 丢弃全透明片段，画草叶。 |
| `3.2.blending_sort` | 按到相机距离排序后绘制半透明窗户。 |
| `5.1.framebuffers` | 场景先渲染到自定义帧缓冲的纹理再贴回屏幕。 |
| `5.2.framebuffers_exercise1` | 练习：用 `1`~`4` 键切换反色/灰度/模糊/锐化内核。 |
| `6.1.cubemaps_skybox` | 加载 6 张面纹理构造天空盒。 |
| `6.2.cubemaps_environment_mapping` | 用 `reflect`/`refract` 做反射与折射球。 |
| `8.advanced_glsl_ubo` | 用 uniform 缓冲对象（UBO）传投影与视图矩阵。 |
| `9.1.geometry_shader_houses` | 几何着色器把点扩展成房子。 |
| `9.2.geometry_shader_exploding` | 几何着色器沿法线炸开模型。 |
| `9.3.geometry_shader_normals` | 几何着色器生成法线可视化线。 |
| `10.1.instancing_quads` | 用 `glDrawArraysInstanced` 一次画 100 个四边形。 |
| `10.2.asteroids` | 无实例化地逐个绘制上万颗小行星（对照性能）。 |
| `10.3.asteroids_instanced` | 用实例化矩阵数组一次性绘制上万颗小行星。 |
| `11.1.anti_aliasing_msaa` | 多重采样帧缓冲（MSAA）减少锯齿。 |
| `11.2.anti_aliasing_offscreen` | 离屏 MSAA：先渲染到多重采样 FBO 再 resolve 到屏幕。 |

## 5.advanced_lighting

| 示例 | 内容 |
| --- | --- |
| `1.advanced_lighting` | Blinn-Phong 光照（半程向量）。 |
| `2.gamma_correction` | sRGB 纹理加载 + 手动 gamma 校正。 |
| `3.1.1.shadow_mapping_depth` | 只渲染深度贴图（调试用）。 |
| `3.1.2.shadow_mapping_base` | 把深度贴图贴到平面上查看。 |
| `3.1.3.shadow_mapping` | 完整平行光阴影映射。 |
| `3.2.1.point_shadows` | 点光源阴影（深度立方体贴图，6 个方向）。 |
| `3.2.2.point_shadows_soft` | 点光源软阴影（对采样方向加扰动）。 |
| `4.normal_mapping` | 法线贴图，从贴图采样法线替换平面法线。 |
| `5.1.parallax_mapping` | 视差贴图，按高度图偏移纹理坐标。 |
| `5.2.steep_parallax_mapping` | 陡峭视差贴图，多层采样提高精度。 |
| `5.3.parallax_occlusion_mapping` | 视差遮蔽映射，采样点与插值搜索。 |
| `6.hdr` | 浮点帧缓冲存 HDR 颜色，再用曝光与色调映射转到屏幕。 |
| `7.bloom` | 提取高亮区域高斯模糊后叠加回场景。 |
| `8.1.deferred_shading` | 延迟着色：G-buffer + 光照阶段。 |
| `8.2.deferred_shading_volumes` | 延迟着色 + 光源体积渲染（几何着色器画光锥/光球）。 |
| `9.ssao` | 屏幕空间环境光遮蔽（SSAO）+ 模糊。 |

## 6.pbr

| 示例 | 内容 |
| --- | --- |
| `1.1.lighting` | 无光照贴图的基础 PBR（Cook-Torrance BRDF）。 |
| `1.2.lighting_textured` | PBR 使用 albedo/normal/metallic/roughness/ao 贴图。 |
| `2.1.1.ibl_irradiance_conversion` | 把 HDR 等距柱状贴图转成立方体贴图。 |
| `2.1.2.ibl_irradiance` | 卷积得到漫反射辐照度贴图（IBL 漫反射）。 |
| `2.2.1.ibl_specular` | 预滤波环境贴图 + BRDF LUT（IBL 镜面反射）。 |
| `2.2.2.ibl_specular_textured` | 在 IBL 镜面反射基础上使用完整 PBR 贴图。 |

## 7.in_practice

| 示例 | 内容 |
| --- | --- |
| `1.debugging` | 打开调试输出（`GL_DEBUG_OUTPUT`）、用 `glGetError`/帧缓冲查看器定位问题。 |

### 运行提示

IBL 类示例（`6.pbr/2.*`）在 llvmpipe 软件渲染下需要约 10 秒完成 HDR 卷积与预滤波，启动后前几秒画面仍为清屏色属正常现象。
