#version 440 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture;

void main()
{
    FragColor = texture2D(texture, TexCoord);
}
