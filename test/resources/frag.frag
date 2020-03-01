#version 440 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Norm;

// texture samplers
uniform sampler2D texture;

void main()
{
    FragColor = vec4(texture2D(texture, TexCoord).xyz, 1 - normalize(Norm).x);
}
