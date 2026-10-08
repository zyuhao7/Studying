# LearningOpenGL

[LearnOpenGL](https://learnopengl.com/) 官方示例的移植集，`src/` 下每个目录是一个独立可运行程序，逐章演示 OpenGL 4.6 core 的一个主题。

示例来自官方 [LearnOpenGL 仓库](https://github.com/JoeyDeVries/LearnOpenGL)，目录名与官方编号一致（如 `src/5.advanced_lighting/9.ssao`）。官方 `CMakeLists.txt` 可构建的 81 个示例中，79 个已移植；`7.in_practice/2.text_rendering` 与 `7.in_practice/3.2d_game` 依赖 freetype/irrKlang，未移植。官方 8.guest 章节与各章的"练习"目录（只给出 GLSL 片段或留白，不是完整程序）同样未移植。

## 目录结构

```
src/<章节组>/<示例>/  示例, 含 main.cpp 与 shader/, 目录名与官方编号一致
include/            第三方头文件
  glad/             OpenGL 4.6 core 加载器 (glad.h + glad.c)
  GLFW/ KHR/        GLFW 与平台头
  glm/ GLM 数学库 (detail/ 随仓库提供, 其余用系统安装)
  imgui/            Dear ImGui
  tools/            Shader / Camera / stb_image / mesh.h / model.h
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

`dir=` 指定示例相对路径（默认 `1.getting_started/2.1.hello_triangle`）：

```bash
make dir=1.getting_started/2.1.hello_triangle   # 编译到 output/main
make dir=1.getting_started/7.4.camera_class run # 编译并运行
make dir=5.advanced_lighting/9.ssao
```

**必须在仓库根目录运行**，示例通过 `argv[1]` 拼接 `./shader/...` 路径，并以 `./static/...` 读取纹理与模型。

批量编译全部示例：

```bash
for f in $(find src -name main.cpp); do d=${f#src/}; make dir=${d%/main.cpp}; done
```

## 运行环境说明

- 需要可用的 OpenGL 4.6 core 环境。WSL2 下依赖 WSLg；若 WSLg 无法创建窗口（`glfwCreateWindow` 卡死），可用 Xvfb 无头运行：`xvfb-run -a -s "-screen 0 1920x1200x24" ./output/main src/<示例>/`。屏幕至少 1600x1200，否则部分示例窗口会被裁剪。
- 需要 GPU 或软件渲染；无 GPU 时可设 `LIBGL_ALWAYS_SOFTWARE=1` 走 llvmpipe。IBL 类示例（`src/6.pbr/2.*`）在 llvmpipe 下要花约 10 秒做 HDR 卷积与预滤波，启动后前几秒画面仍是清屏色属正常。

## 操作方式

- 全部示例：`ESC` 退出。
- 相机类示例（`1.getting_started/7.x` 起）：`W/A/S/D` 前后左右移动，鼠标拖动旋转视角、滚轮缩放。

各示例的演示内容见 [docs/EXAMPLES.md](docs/EXAMPLES.md)；学习路线与"小型模型查看器"练习的实施方案见 [docs/MODEL_VIEWER.md](docs/MODEL_VIEWER.md)。

## 构建注意事项

- `lib/` 中的静态库是 MinGW 产物，Linux 下不可链接，因此 Linux 分支不添加 `-Llib`，改用系统 glfw3/assimp。
- `include/glad/glad.c` 由 glad 0.1.36 按 `glad.h` 的生成参数（`--profile core --api gl=4.6 --generator c --extensions ""`）生成，两者必须版本一致，否则函数指针表错位。
- `include/glm/detail/` 为 0.9.9.8 局部副本，与系统 `libglm-dev` 0.9.9.8 同版本，混用安全。
- 原先随仓库的 `include/assimp/` 只有 41 个头文件且版本与 `libassimp` 不一致，链接后 `aiString`/材质数据错位，模型纹理会解析成被截断的文件名（例如 `arm_dif.png` 变成 `dif.png`），导致贴图全部加载失败。已删除该目录，统一使用 `libassimp-dev` 的头文件与库（两者版本必须一致）。
- 官方示例改用本项目约定：着色器经 `Shader("./shader/...")` 加载（构造函数把 `Shader::dirName` 插到路径第 2 个字符处，故路径必须以 `./` 开头），资源路径统一写成相对仓库根的 `./static/...`。
- `-Wall -Wextra` 下存在大量 `unused parameter/variable` 警告，属教程代码遗留，不影响运行。
- 每个含 `stb_image` 的翻译单元各自 `#define STB_IMAGE_IMPLEMENTATION`；每个含 ImGui 的示例各自编译一份 ImGui 实现。
- `static/` 只保留当前示例引用的资源（backpack、nanosuit、planet、rock 与各章纹理）；纹理经 `.mtl` 间接引用，不要按字面路径判断是否用到。
