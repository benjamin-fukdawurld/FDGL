#version 440 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Norm;
in vec3 Pos;

struct Light
{
    vec3 position; // location + 0
    vec4 ambientColor; // location + 1
    vec4 diffuseColor;  // location + 2
    vec4 specularColor; // location + 3
    float constantAttenuation; // location + 4
    float linearAttenuation; // location + 5
    float quadraticAttenuation;  // location + 6
};

struct Material
{
    vec3 ambientColor; // location + 0
    vec3 diffuseColor; // location + 1
    vec3 specularColor; // location + 2
    float shininess; // location + 3
};

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

layout(location = 3) uniform vec3 camPos;
layout(location = 4) uniform Light light;

layout(location = 11) uniform Material mat;

// texture samplers
uniform sampler2D texture;

float getAttenuation(float distance)
{
    return 1/(light.constantAttenuation + light.linearAttenuation * distance
              + light.quadraticAttenuation * distance * distance);
}

vec4 getAmbientLight(float attenuation)
{
    return vec4(light.ambientColor.rgb * attenuation, light.ambientColor.a);
}

vec4 getDiffuseLight(vec3 n, vec3 lightDir)
{
    float diff = max(dot(n, lightDir), 0.0);
    return vec4(light.diffuseColor.rgb * diff, light.diffuseColor.a);
}

vec4 getSpecularLight(vec3 n, vec3 lightDir)
{
    vec3 camDir = normalize(camPos - Pos);
    vec3 reflectDir = reflect(-lightDir, n);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), mat.shininess);
    return vec4(light.specularColor.xyz * mat.specularColor.xyz * spec, light.specularColor.a);
}

void main()
{
    vec3 n = normalize(Norm);
    vec3 lightDir = normalize(light.position - Pos);
    float dist = distance(Pos, light.position);
    float attenuation = getAttenuation(dist);

    vec4 ambientLight = getAmbientLight(attenuation);
    vec4 diffuseLight = getDiffuseLight(n, lightDir);
    vec4 specularLight = getSpecularLight(n, lightDir);

    FragColor = vec4(texture2D(texture, TexCoord).xyz, 1) * (ambientLight + diffuseLight + specularLight);
}
