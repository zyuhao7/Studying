#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoords;

out vec2 outTexCoord;
out vec3 outNormal;
out vec3 outFragPos;

uniform float factor;

uniform mat4 model; // 模型矩阵
uniform mat4 view; // 视图矩阵
uniform mat4 projection; // 投影矩阵

void main() {

  gl_Position = projection * view * model * vec4(Position, 1.0f);

  outFragPos = vec3(model * vec4(Position, 1.0));

  outTexCoord = TexCoords;
  // 解决不等比缩放，对法向量产生的影响
  outNormal = mat3(transpose(inverse(model))) * Normal;
}