# 示例说明

每个示例都是独立可运行程序，构建与运行方式统一：

```bash
make dir=<示例相对路径> run     # 在仓库根目录执行
```

示例从官方 [LearnOpenGL 仓库](https://github.com/JoeyDeVries/LearnOpenGL) 移植，目录名与官方编号一致。除特别说明外，操作均为 `ESC` 退出；相机类示例额外支持 `W/A/S/D` 移动与鼠标拖动转向。

未移植的官方目录：`8.guest` 全章、`7.in_practice/2.text_rendering`、`7.in_practice/3.2d_game`（缺 freetype/irrKlang 依赖）、各章的"练习"目录（只给 GLSL 片段或留白，非完整程序），以及 `5.advanced_lighting/3.3.csm`（官方该目录实为深度可视化示例的副本，不在 `CMakeLists.txt` 构建列表内）。

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
