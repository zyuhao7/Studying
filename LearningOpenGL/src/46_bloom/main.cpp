#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <tools/shader.h>
#include <tools/camera.h>
#include <geometry/BoxGeometry.h>
#include <geometry/PlaneGeometry.h>
#include <geometry/SphereGeometry.h>

#define STB_IMAGE_IMPLEMENTATION
#include <tools/stb_image.h>

#include <tools/gui.h>

#include <tools/mesh.h>
#include <tools/model.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const *path);
unsigned int loadCubemap(vector<std::string> faces);

void drawSkyBox(Shader shader, BoxGeometry geometry, unsigned int cubeMap);

// method
void drawMesh(BufferGeometry geometry);
void drawLightObject(Shader shader, BufferGeometry geometry, glm::vec3 position);
void RenderQuad();

std::string Shader::dirName;

// int SCREEN_WIDTH = 800;
// int SCREEN_HEIGHT = 600;
int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 1200;

// camera value
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// delta time
float deltaTime = 0.0f;
float lastTime = 0.0f;

float lastX = SCREEN_WIDTH / 2.0f; // 鼠标上一帧的位置
float lastY = SCREEN_HEIGHT / 2.0f;

Camera camera(glm::vec3(0.0, 1.0, 6.0));

using namespace std;

int main(int argc, char *argv[])
{
  Shader::dirName = argv[1];
  glfwInit();
  // 设置主要和次要版本
  const char *glsl_version = "#version 330";

  // 片段着色器将作用域每一个采样点（采用4倍抗锯齿，则每个像素有4个片段（四个采样点））
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // 窗口对象
  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // -----------------------
  // 创建imgui上下文
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // 设置样式
  ImGui::StyleColorsDark();
  // 设置平台和渲染器
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  // -----------------------

  // 设置视口
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glEnable(GL_PROGRAM_POINT_SIZE);

  // 启用混合
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // 深度测试
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // 鼠标键盘事件
  // 1.注册窗口变化监听
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // 2.鼠标事件
  glfwSetCursorPosCallback(window, mouse_callback);
  // 3.将鼠标隐藏
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Shader sceneShader("./shader/scene_vert.glsl", "./shader/scene_frag.glsl");
  // Shader hdrShader("./shader/hdr_quad_vert.glsl", "./shader/hdr_quad_frag.glsl");
  // Shader lightObjectShader("./shader/light_object_vert.glsl", "./shader/light_object_frag.glsl");

  Shader sceneShader("./shader/bloom_scene_vert.glsl", "./shader/bloom_scene_frag.glsl");
  Shader lightShader("./shader/light_object_vert.glsl", "./shader/light_object_frag.glsl");
  Shader blurShader("./shader/blur_scene_vert.glsl", "./shader/blur_scene_frag.glsl");
  Shader finalShader("./shader/bloom_final_vert.glsl", "./shader/bloom_final_frag.glsl");

  PlaneGeometry groundGeometry(10.0, 10.0);           // 地面
  PlaneGeometry grassGeometry(1.0, 1.0);              // 草丛
  BoxGeometry boxGeometry(1.0, 1.0, 1.0);             // 盒子
  SphereGeometry pointLightGeometry(0.2, 50.0, 50.0); // 点光源位置显示

  PlaneGeometry quadGeometry(2.0, 2.0); // hdr输出平面

  unsigned int woodMap = loadTexture("./static/texture/wood.png");                         // 地面
  unsigned int brickMap = loadTexture("./static/texture/brick_diffuse.jpg");               // 砖块
  unsigned int grassMap = loadTexture("./static/texture/blending_transparent_window.png"); // 草丛

  float factor = 0.0;

  unsigned int hdrFBO;
  glGenFramebuffers(1, &hdrFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

  // 创建两个颜色缓冲区，一个用于渲染，一个用于亮度提取
  // **********************
  unsigned int colorBuffers[2];
  glGenTextures(2, colorBuffers);
  for (unsigned int i = 0; i < 2; i++)
  {
    glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // 避免模糊过滤器重复采样
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
  }
  unsigned int rboDepth;
  glGenRenderbuffers(1, &rboDepth);
  glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
  // 使用帧缓冲区的颜色附件
  unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
  glDrawBuffers(2, attachments);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "Framebuffer not complete!" << std::endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // 创建用于模糊的帧缓冲区
  // **********************
  unsigned int pingpongFBO[2];
  unsigned int pingpongColorbuffers[2];
  glGenFramebuffers(2, pingpongFBO);
  glGenTextures(2, pingpongColorbuffers);
  for (unsigned int i = 0; i < 2; i++)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
    glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Framebuffer not complete!" << std::endl;
  }

  // 点光源的位置
  glm::vec3 pointLightPositions[] = {
      glm::vec3(0.7f, 1.0f, 1.5f),
      glm::vec3(2.3f, 3.0f, -4.0f),
      glm::vec3(-4.0f, 2.0f, 1.0f),
      glm::vec3(1.4f, 2.0f, 1.3f)};

  // 点光源颜色
  glm::vec3 pointLightColors[] = {
      glm::vec3(2.0f, 1.0f, 1.0f),
      glm::vec3(4.0f, 0.0f, 4.0f),
      glm::vec3(1.0f, 1.0f, 4.0f),
      glm::vec3(0.0f, 2.0f, 0.0f)};

  // 草的位置
  vector<glm::vec3> grassPositions{
      glm::vec3(-1.5f, 0.5f, -0.48f),
      glm::vec3(1.5f, 0.5f, 0.51f),
      glm::vec3(0.0f, 0.5f, 0.7f),
      glm::vec3(-0.3f, 0.5f, -2.3f),
      glm::vec3(-1.9f, 0.5f, -2.0f)};

  glm::vec3 lightPosition = glm::vec3(1.0, 2.5, 2.0); // 光照位置

  blurShader.use();
  blurShader.setInt("image", 0);

  finalShader.use();
  finalShader.setInt("scene", 0);
  finalShader.setInt("bloomBlur", 1);

  // 设置平行光光照属性
  sceneShader.use();
  sceneShader.setInt("diffuseTexture", 0);

  sceneShader.setVec3("directionLight.ambient", 0.01f, 0.01f, 0.01f);
  sceneShader.setVec3("directionLight.diffuse", 0.05f, 0.05f, 0.05f); // 将光照调暗了一些以搭配场景
  sceneShader.setVec3("directionLight.specular", 1.0f, 1.0f, 1.0f);

  // 设置衰减
  sceneShader.setFloat("light.constant", 1.0f);
  sceneShader.setFloat("light.linear", 0.09f);
  sceneShader.setFloat("light.quadratic", 0.032f);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastTime;
    lastTime = currentFrame;

    // 在标题中显示帧率信息
    // *************************************************************************
    int fps_value = (int)round(ImGui::GetIO().Framerate);
    int ms_value = (int)round(1000.0f / ImGui::GetIO().Framerate);

    std::string FPS = std::to_string(fps_value);
    std::string ms = std::to_string(ms_value);
    std::string newTitle = "LearnOpenGL - " + ms + " ms/frame " + FPS;
    glfwSetWindowTitle(window, newTitle.c_str());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // *************************************************************************

    // 渲染指令
    // ...
    glClearColor(25.0 / 255.0, 25.0 / 255.0, 25.0 / 255.0, 1.0);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sceneShader.use();

    factor = glfwGetTime();
    sceneShader.setFloat("factor", -factor * 0.3);

    // 修改光源颜色
    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, woodMap);

    float radius = 5.0f;
    float camX = sin(glfwGetTime() * 0.5) * radius;
    float camZ = cos(glfwGetTime() * 0.5) * radius;

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    glm::vec3 lightPos = glm::vec3(lightPosition.x * glm::sin(glfwGetTime()) * 2.0, lightPosition.y, lightPosition.z);
    sceneShader.use();
    sceneShader.setMat4("view", view);
    sceneShader.setMat4("projection", projection);

    sceneShader.setVec3("directionLight.direction", lightPos); // 光源位置
    sceneShader.setVec3("viewPos", camera.Position);

    pointLightPositions[0].z = camZ;
    pointLightPositions[0].x = camX;

    for (unsigned int i = 0; i < 4; i++)
    {

      // 设置点光源属性
      sceneShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
      sceneShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.01f, 0.01f, 0.01f);
      sceneShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", pointLightColors[i]);
      sceneShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);

      // // 设置衰减
      sceneShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
      sceneShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
      sceneShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
    }

    // 绘制地板
    // ********************************************************
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));

    sceneShader.setFloat("uvScale", 4.0f);
    sceneShader.setMat4("model", model);
    drawMesh(groundGeometry);
    // ********************************************************

    // 绘制砖块
    // ----------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, brickMap);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0, 1.0, -1.0));
    model = glm::scale(model, glm::vec3(2.0, 2.0, 2.0));

    sceneShader.setFloat("uvScale", 1.0f);
    sceneShader.setMat4("model", model);
    drawMesh(boxGeometry);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0, 0.5, 2.0));
    sceneShader.setMat4("model", model);
    drawMesh(boxGeometry);
    // ----------------------------------------------------------

    // 绘制草丛面板
    // ----------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, grassMap);

    // 对透明物体进行动态排序
    std::map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < grassPositions.size(); i++)
    {
      float distance = glm::length(camera.Position - grassPositions[i]);
      sorted[distance] = grassPositions[i];
    }

    for (std::map<float, glm::vec3>::reverse_iterator iterator = sorted.rbegin(); iterator != sorted.rend(); iterator++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, iterator->second);
      sceneShader.setMat4("model", model);
      drawMesh(grassGeometry);
    }
    // ----------------------------------------------------------

    // 绘制灯光物体
    // ************************************************************
    lightShader.use();
    lightShader.setMat4("view", view);
    lightShader.setMat4("projection", projection);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);

    lightShader.setMat4("model", model);
    lightShader.setVec3("lightColor", glm::vec3(2.0f, 2.0f, 2.0f));

    drawMesh(pointLightGeometry);

    for (unsigned int i = 0; i < 4; i++)
    {
      model = glm::mat4(1.0f);
      model = glm::translate(model, pointLightPositions[i]);

      lightShader.setMat4("model", model);
      lightShader.setVec3("lightColor", pointLightColors[i]);

      drawMesh(pointLightGeometry);
    }
    // ************************************************************

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2.高斯模糊明亮的片段
    bool horizontal = true, first_iteration = true;
    unsigned int amount = 10;
    blurShader.use();
    for (unsigned int i = 0; i < amount; i++)
    {
      glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
      blurShader.setInt("horizontal", horizontal);
      glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);
      drawMesh(quadGeometry);
      horizontal = !horizontal;
      if (first_iteration)
      {
        first_iteration = false;
      }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3.绘制hdr输出的texture
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    finalShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
    finalShader.setInt("bloom", true);
    finalShader.setFloat("exposure", 1.0);
    drawMesh(quadGeometry);

    // 渲染 gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

// 绘制物体
void drawMesh(BufferGeometry geometry)
{
  glBindVertexArray(geometry.VAO);
  glDrawElements(GL_TRIANGLES, geometry.indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

// 绘制灯光物体
void drawLightObject(Shader shader, BufferGeometry geometry, glm::vec3 position)
{
  glm::mat4 view = camera.GetViewMatrix();
  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

  // // 绘制灯光物体
  shader.use();
  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  model = glm::mat4(1.0f);
  model = glm::translate(model, position);

  shader.setMat4("model", model);
  shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
  drawMesh(geometry);
}

// 窗口变动监听
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// 键盘输入监听
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }

  // 相机按键控制
  // 相机移动
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(RIGHT, deltaTime);
  }
}

// 鼠标移动监听
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// 加载纹理贴图
unsigned int loadTexture(char const *path)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);

  // 图像y轴翻转
  stbi_set_flip_vertically_on_load(true);
  int width, height, nrComponents;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

// 加载立方体贴图

unsigned int loadCubemap(vector<std::string> faces)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  // 此处需要将y轴旋转关闭，若之前调用过loadTexture
  stbi_set_flip_vertically_on_load(false);

  int width, height, nrChannels;
  for (unsigned int i = 0; i < faces.size(); i++)
  {
    unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                   0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    }
    else
    {
      std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
      stbi_image_free(data);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}

// *******************method*********************
void drawSkyBox(Shader shader, BoxGeometry geometry, unsigned int cubeMap)
{

  glDepthFunc(GL_LEQUAL);
  glDisable(GL_DEPTH_TEST);

  glm::mat4 view = camera.GetViewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

  shader.use();
  view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // 移除平移分量

  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
  glBindVertexArray(geometry.VAO);
  glDrawElements(GL_TRIANGLES, geometry.indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  view = camera.GetViewMatrix();
}

// RenderQuad() Renders a 1x1 quad in NDC
GLuint quadVAO = 0;
GLuint quadVBO;
void RenderQuad()
{
  if (quadVAO == 0)
  {
    // positions
    glm::vec3 pos1(-1.0, 1.0, 0.0);
    glm::vec3 pos2(-1.0, -1.0, 0.0);
    glm::vec3 pos3(1.0, -1.0, 0.0);
    glm::vec3 pos4(1.0, 1.0, 0.0);
    // texture coordinates
    glm::vec2 uv1(0.0, 1.0);
    glm::vec2 uv2(0.0, 0.0);
    glm::vec2 uv3(1.0, 0.0);
    glm::vec2 uv4(1.0, 1.0);
    // normal vector
    glm::vec3 nm(0.0, 0.0, 1.0);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // - triangle 1
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // - triangle 2
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);

    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);

    GLfloat quadVertices[] = {
        // Positions            // normal         // TexCoords  // Tangent                          // Bitangent
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z};
    // Setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid *)(11 * sizeof(GLfloat)));
  }
  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}