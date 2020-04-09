#version 440 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Norm;

layout(location = 3) uniform vec4 lightColor;
layout(location = 4) uniform vec4 lightPos;

// texture samplers
uniform sampler2D texture;

void main()
{
    FragColor = vec4(texture2D(texture, TexCoord).xyz, 1 - normalize(Norm).x) * lightColor;
}
