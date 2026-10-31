#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
// 0 = texture1 only, 1 = texture2 only
uniform float uMix;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), uMix);
}