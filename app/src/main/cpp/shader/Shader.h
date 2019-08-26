//
// Created by yuanbin on 19-8-12.
//

#pragma once

static const char BGVertexShader[] = R"(
#version 300 es
layout (location = 0) in vec3 aPos;

out vec3 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
void main() {
  gl_Position = projection * view * transform * vec4(aPos, 1.0);
  TexCoord = aPos;
}
)";

static const char BGFragmentShader[] = R"(
#version 300 es
out vec4 FragColor;

in vec3 TexCoord;
uniform samplerCube skybox;

void main() {
    FragColor = texture(skybox, TexCoord);
    FragColor.w = 1.0;
}
)";

static const char vertexShader[] = R"(
#version 300 es
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main() {
  gl_Position = projection * view * transform * vec4(aPos, 1.0);
}
)";

static const char fragmentShader[] = R"(
#version 300 es
out vec4 FragColor;
uniform vec4 color;

void main() {
    FragColor = color;
}
)";

static const char lightVertexShader[] = R"(
#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec4 pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main() {
  pos = transform * vec4(aPos, 1.0);
  gl_Position = projection * view * pos;
  normal = mat3(transpose(inverse(transform))) * aNormal;
}
)";

static const char lightFragmentShader[] = R"(
#version 300 es
out vec4 FragColor;

in vec4 pos;
in vec3 normal;

uniform vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 cameraPos;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - pos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - pos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * color.xyz;
    FragColor = vec4(result, color.w);
}
)";
