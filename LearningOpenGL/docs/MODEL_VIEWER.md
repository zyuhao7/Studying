# 学习路线与练习成果：小型模型查看器

来源：`standard.txt`。本文把它拆成"先跑哪些示例 → 再做什么工具 → 怎么验收"，并回答关于 Qt 的问题。

## 一、学习路线对应到本仓库示例

标准要求的前四块，本仓库都有对应示例，按顺序跑即可。

| 标准里的模块 | 本仓库示例 |
| --- | --- |
| 窗口 | `1.getting_started/1.1.hello_window`、`1.2.hello_window_clear` |
| 三角形 | `1.getting_started/2.1` – `2.5`（顶点属性、EBO、多个 VAO） |
| Shader | `1.getting_started/3.1.shaders_uniform`、`3.2.shaders_interpolation`、`3.3.shaders_class` |
| 纹理 | `1.getting_started/4.1.textures`、`4.2.textures_combined`、`4.4` – `4.6`（练习） |
| 变换 | `1.getting_started/5.1.transformations`、`5.2` |
| 摄像机 | `1.getting_started/6.1` – `6.3.coordinate_systems_*`、`7.1` – `7.4.camera_class` |
| 基础光照 | `2.lighting/1.colors`、`2.1.basic_lighting_diffuse`、`2.2.basic_lighting_specular` |
| 材质 | `2.lighting/3.1.materials`、`3.2.materials_exercise1` |
| 多光源 | `2.lighting/4.1` – `4.4.lighting_maps_*`、`5.1` – `5.4.light_casters_*`、`6.multiple_lights` |
| 模型与网格组织 | `3.model_loading/1.model_loading`（`include/tools/model.h` + `mesh.h`） |
| 深度测试 | `4.advanced_opengl/1.1.depth_testing`、`1.2.depth_testing_view` |
| 帧缓冲 | `4.advanced_opengl/5.1.framebuffers`、`5.2.framebuffers_exercise1` |
| 实例化 | `4.advanced_opengl/10.1.instancing_quads`、`10.2.asteroids`、`10.3.asteroids_instanced` |

跑法见 [README](../README.md)，各示例效果见 [EXAMPLES.md](EXAMPLES.md)。

## 二、练习成果：小型模型查看器

标准要求五项功能，逐项给出可直接复用的示例代码位置。

| 功能 | 做法 | 可复用示例 |
| --- | --- | --- |
| 加载并显示模型 | `Model("./static/model/<name>/<name>.obj")`，光照用现有的 PBR/Phong 着色器 | `3.model_loading/1.model_loading`、`include/tools/model.h` |
| 鼠标旋转、缩放 | 拖动改 `yaw/pitch`，滚轮改 `Zoom`（FOV） | `1.getting_started/7.3.camera_mouse_zoom`、`7.4.camera_class` |
| 鼠标平移 | 现有 `Camera` 没有 pan，需自行加：中键拖动时按 `right`/`up` 向量平移 `Position` | `7.4.camera_class`（在 `Camera` 上扩展） |
| 调整光源与材质 | 光源位置/颜色/衰减 + 材质 `ambient/diffuse/specular/shininess` 用滑块驱动 | `2.lighting/3.1.materials`、`5.2.light_casters_point` |
| 显示坐标轴 | 画 3 条 `GL_LINES`（X 红 / Y 绿 / Z 蓝），单独一个不参与光照的着色器 | `2.lighting/1.colors`（画光源立方体的写法） |
| 显示包围盒 | 遍历 `mesh.vertices` 求 AABB（min/max），再据此画 12 条边 | `include/tools/mesh.h`（顶点数据）+ `2.lighting/1.colors` |
| 帧时间 | 每帧测 `deltaTime`，滑动平均后显示 | 任意示例的 `deltaTime` 计时 |
| 顶点数 | 加载时累加各 `Mesh` 的 `vertices.size()` | `include/tools/model.h`、`mesh.h` |

建议顺序：先把 `3.model_loading/1.model_loading` 跑通 → 把相机换成 `7.4.camera_class` 的做法 → 加坐标轴/包围盒 → 最后接面板。

## 三、验收问题：一个顶点如何从模型坐标变成屏幕上的像素

按流水线顺序答，每一步都能在本仓库里指到对应示例：

1. **模型空间 → 世界空间**：左乘 `model` 矩阵（平移/旋转/缩放）。
2. **世界空间 → 观察空间**：左乘 `view`（`glm::lookAt(eye, target, up)`）。
3. **观察空间 → 裁剪空间**：左乘 `projection`（`glm::perspective`），得到齐次坐标 `gl_Position`。
   —— 上面三步在顶点着色器里一次完成，见 `1.getting_started/5.1.transformations`、`6.1.coordinate_systems`；需要时可用 `4.advanced_opengl/8.advanced_glsl_ubo` 把矩阵放进 UBO。
4. **透视除法**：`gl_Position.xyz / gl_Position.w` → 归一化设备坐标（NDC，x/y/z ∈ [-1, 1]）。
5. **视口变换**：`glViewport` 把 NDC 映射到窗口像素坐标。
6. **图元装配与光栅化**：把顶点连成三角形，逐像素生成片段；顶点属性（颜色、纹理坐标）在此线性插值，见 `1.getting_started/3.2.shaders_interpolation`。
7. **片段着色器**：算颜色，采样纹理；纹理坐标来自顶点属性插值，见 `1.getting_started/4.1.textures`。
8. **逐片段测试**：深度测试决定是否覆盖已有像素（`4.advanced_opengl/1.1.depth_testing`），模板测试（`2.stencil_testing`）、混合（`3.2.blending_sort`）同理。
9. **写入帧缓冲**：最终颜色落到默认帧缓冲，再交换到屏幕；若要二次处理则先写离屏帧缓冲（`4.advanced_opengl/5.1.framebuffers`）。

一句话概括：**model → view → projection 三次矩阵变换进裁剪空间，除以 w 得 NDC，视口变换到像素，光栅化成片段，片段着色器上色后经深度/混合测试写入帧缓冲。**

## 四、有必要用 Qt 做工具面板吗

**结论：这个练习没必要。用仓库里已经装好的 Dear ImGui 就够，Qt 只在另一种交付目标下才值得。**

理由：

1. **现成且零依赖成本**。`include/imgui/` 已在仓库，`Makefile` 无条件把 ImGui 的 5 个 `.cpp` 编进每个示例，加面板只需 `ImGui::CreateContext` + 每帧 `ImGui::Begin/End`。帧时间、顶点数、光源/材质滑块都是一行 `ImGui::SliderFloat`。
2. **上下文冲突**。Qt 的 `QOpenGLWidget` 自己持有 GL 上下文与事件循环，和示例里的 `glfwCreateWindow`/`glfwPollEvents` 不能共存；硬接要先把窗口层整个换成 Qt（换上下文初始化、换输入回调、换窗口尺寸处理），学习时间全花在框架适配上，和"把三维知识学明白"的目标无关。
3. **学习目标不在这**。本题的验收是能解释渲染流水线，不是 GUI 框架熟练度。面板只是调试手段，面板越省事，越有余力调相机和光照。

**什么时候才值得上 Qt**：需要原生菜单栏、可停靠面板、文件选择对话框、或要交付一个能给非开发者双击运行的桌面程序。真要上，正确姿势是 **Qt6 只做外壳**——`QOpenGLWidget` 提供上下文和事件循环，渲染/相机/模型代码原样复用，绝不要在 Qt 里再嵌一个 GLFW 窗口。也可以在 ImGui 版本跑通后再迁移，届时渲染层代码不用动。
