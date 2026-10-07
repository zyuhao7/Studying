# LearningOpenGL

LearnOpenGL 教程配套示例集，`src/` 下每个目录是一个独立可运行程序，逐章演示 OpenGL 4.6 core 的一个主题。

## 目录结构

```
src/<章节>/         每个示例独立目录, 含 main.cpp 与 shader/
include/            第三方与自研头文件
  glad/             OpenGL 4.6 core 加载器 (glad.h + glad.c)
  GLFW/ KHR/        GLFW 与平台头
  glm/ GLM 数学库 (detail/ 随仓库提供, 其余用系统安装)
  imgui/            Dear ImGui
  geometry/         BoxGeometry / PlaneGeometry / SphereGeometry
  tools/            Shader / Camera / Gui / stb_image / mesh.h / model.h
static/             纹理与模型资源 (texture/、model/)
lib/                Windows (MinGW) 预编译静态库
output/             构建产物
```

## 依赖

**Linux (Ubuntu/Debian)**

```bash
sudo apt-get install -y build-essential libglfw3-dev libglm-dev libassimp-dev
```

**Windows (MinGW)**

使用 `lib/` 下的预编译库（`libglad.a`、`libglfw3.a`、`libassimp.dll.a`），运行时需要 `output/` 下的 DLL。

## 构建与运行

单目录方式，`dir=` 指定示例目录名（默认 `05_shader_class`）：

```bash
make dir=07_load_texture     # 编译到 output/main
make dir=07_load_texture run # 编译并运行
make dir=07_load_texture clean
```

**必须在仓库根目录运行**，示例通过 `argv[1]` 拼接 `./shader/...` 路径，并以 `./static/...` 读取纹理与模型。

批量编译全部示例：

```bash
for p in src/*/; do d=${p#src/}; make dir=${d%/}; done
```

## 运行环境说明

- 需要可用的 OpenGL 4.6 core 环境。WSL2 下依赖 WSLg；若 WSLg 无法创建窗口（`glfwCreateWindow` 卡死），可用 Xvfb 无头运行：`xvfb-run -a -s "-screen 0 1920x1200x24" ./output/main src/<章节>/`。屏幕至少 1600x1200，否则 41/42/45/46/47 等窗口会被裁剪。
- 需要 GPU 或软件渲染；无 GPU 时可设 `LIBGL_ALWAYS_SOFTWARE=1` 走 llvmpipe。

## 操作方式

- 全部示例：`ESC` 退出。
- 相机类示例（16 章起）：`W/A/S/D` 前后左右移动，鼠标拖动旋转视角。

各示例的演示内容、操作与预期效果见 [docs/EXAMPLES.md](docs/EXAMPLES.md)。

## 构建注意事项

- `lib/` 中的静态库是 MinGW 产物，Linux 下不可链接，因此 Linux 分支不添加 `-Llib`，改用系统 glfw3/assimp。
- `include/glad/glad.c` 由 glad 0.1.36 按 `glad.h` 的生成参数（`--profile core --api gl=4.6 --generator c --extensions ""`）生成，两者必须版本一致，否则函数指针表错位。
- `include/glm/detail/` 为 0.9.9.8 局部副本，与系统 `libglm-dev` 0.9.9.8 同版本，混用安全。
- 原先随仓库的 `include/assimp/` 只有 41 个头文件且版本与 `libassimp` 不一致，链接后 `aiString`/材质数据错位，模型纹理会解析成被截断的文件名（例如 `arm_dif.png` 变成 `dif.png`），导致贴图全部加载失败。已删除该目录，统一使用 `libassimp-dev` 的头文件与库（两者版本必须一致）。
- `include/geometry/BufferGeometry.h` 与 `include/tools/mesh.h` 共用同一个 `Vertex` 结构，用宏 `TOOLS_VERTEX_DEFINED` 防止重复定义。
- `47_deferred_shading` 的 G-buffer 用了 RGB16F 三通道附件；示例沿用其它章节的全局 `glEnable(GL_BLEND)`，在部分驱动（llvmpipe 等）下会丢弃这些附件的写入，导致画面只剩清屏色。已在几何阶段前 `glDisable(GL_BLEND)`、结束后恢复。
- `-Wall -Wextra` 下存在大量 `unused parameter/variable` 警告，属教程代码遗留，不影响运行。
