#version 440 core

layout(location = 4) uniform vec4 lightColor;

out vec4 color;

void main(void)
{
    color = lightColor;
}
