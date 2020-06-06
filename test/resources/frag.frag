#version 440 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Norm;
in vec3 Pos;

struct Light
{
    vec3 position; // location + 0
    vec3 direction; // location + 1
    vec4 ambientColor; // location + 2
    vec4 diffuseColor;  // location + 3
    vec4 specularColor; // location + 4
    float constantAttenuation; // location + 5
    float linearAttenuation; // location + 6
    float quadraticAttenuation;  // location + 7
};

struct Material
{
    sampler2D ambientTexture; // location + 0
    sampler2D diffuseTexture; // location + 1
    sampler2D specularTexture; // location + 2
    vec3 ambientColor; // location + 3
    vec3 diffuseColor; // location + 4
    vec3 specularColor; // location + 5
    float shininess; // location + 6
};

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

layout(location = 3) uniform vec3 camPos;
layout(location = 4) uniform Light light;

layout(location = 12) uniform Material mat;

vec3 getLightDirection(const in Light l, const in vec3 fragPosition)
{
    return normalize(l.position - fragPosition);
}

float getAttenuation(float distance, const in Light l)
{
    return 1/(l.constantAttenuation + l.linearAttenuation * distance
              + l.quadraticAttenuation * distance * distance);
}

vec4 getAmbientLight(float attenuation, const in Light l, const in Material m)
{
    return vec4(m.ambientColor * l.ambientColor.rgb * attenuation, l.ambientColor.a);
}

vec4 getDiffuseLight(vec3 n, vec3 lightDir, const in Light l, const in Material m)
{
    float diff = max(dot(n, lightDir), 0.0);
    return vec4(m.diffuseColor * l.diffuseColor.rgb * diff, light.diffuseColor.a);
}

vec4 getSpecularLight(vec3 n, vec3 lightDir, const in Light l, const in Material m)
{
    vec3 camDir = normalize(camPos - Pos);
    vec3 reflectDir = reflect(-lightDir, n);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), m.shininess);
    return vec4(l.specularColor.rgb * m.specularColor.rgb * spec, l.specularColor.a);
}

vec4 computeFragmentColor(const in Light l, const in Material m, const in vec3 fragmentPosition, const in vec3 normal)
{
    vec3 lightDir = getLightDirection(l, Pos);
    vec4 ambient = texture2D(mat.ambientTexture, TexCoord) * getAmbientLight(getAttenuation(distance(Pos, l.position), l), l, m);
    vec4 diffuse = texture2D(mat.diffuseTexture, TexCoord) * getDiffuseLight(normal, lightDir, l, m);
    vec4 specular = texture2D(mat.specularTexture, TexCoord) * getSpecularLight(normal, lightDir, l, m);

    return ambient + diffuse + specular;
}

void main()
{
    vec3 n = normalize(Norm);
    FragColor = computeFragmentColor(light, mat, Pos, n);
}
