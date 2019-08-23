//
// Created by yuanbin on 19-8-12.
//

#pragma once

static const char gVertexShader[] = R"(
#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main() {

  FragPos = transform * vec4(aPos, 1.0);
  gl_Position = projection * view * FragPos;
  Normal = mat3(transpose(inverse(transform))) * aNormal;
}
)";

static const char gFragmentShader[] = R"(
#version 300 es
out vec4 FragColor;

in vec3 Normal;
in vec4 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
)";

static const char lightVertexShader[] = R"(
#version 300 es
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
void main() {
  gl_Position = projection * view * transform * vec4(aPos, 1.0);
}
)";

static const char lightFragmentShader[] = R"(
#version 300 es
out vec4 FragColor;
uniform vec4 color;

void main() {
    FragColor = color;
}
)";