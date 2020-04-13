#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Norm;
out vec3 Pos;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

void main()
{
    vec4 p = model * vec4(aPos, 1.0f);
    gl_Position = projection * view * p;
    Norm = mat3(model) * aNorm;
    Pos = p.xyz;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
