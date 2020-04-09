#version 440 core

layout(location = 0) uniform vec3 lightPosition;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

layout(location = 3) uniform float scale;

const int indices[36] = int[36](
    0, 1, 2,
    2, 1, 3,

    4, 5, 6,
    6, 5, 7,

    5, 0, 7,
    7, 0, 2,

    1, 4, 3,
    3, 4, 6,

    5, 4, 0,
    0, 4, 1,

    2, 3, 7,
    7, 3, 6
);

const vec3 vertices[8] = vec3[8](
    vec3(-1.0f, -1.0f, -1.0f),
    vec3(1.0f, -1.0f, -1.0f),
    vec3(-1.0f, 1.0f, -1.0f),
    vec3(1.0f, 1.0f, -1.0f),
    vec3(1.0f, -1.0f, 1.0f),
    vec3(-1.0f, -1.0f, 1.0f),
    vec3(1.0f, 1.0f, 1.0f),
    vec3(-1.0f, 1.0f, 1.0f)
);

void main()
{
    vec3 pos = vertices[indices[gl_VertexID]] * scale + lightPosition;
    gl_Position = projection * view * vec4(pos, 1.0f);
}
