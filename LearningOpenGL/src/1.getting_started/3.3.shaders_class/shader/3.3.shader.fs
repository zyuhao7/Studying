#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform float uTime;

void main()
{
    // slide between the interpolated color and its complement
    float t = sin(uTime) * 0.5 + 0.5;
    vec3 color = mix(ourColor, 1.0 - ourColor, t);
    FragColor = vec4(color, 1.0f);
}