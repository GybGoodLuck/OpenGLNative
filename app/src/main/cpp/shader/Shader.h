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
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
uniform bool isGaussian;
out vec2 TexCoords;

void main() {
    if (isGaussian) {
        gl_Position = vec4(aPos, 1.0);
    } else {
        gl_Position = projection * view * transform * vec4(aPos, 1.0);
    }
    TexCoords = aTexCoords;
}
)";

static const char fragmentShader[] = R"(
#version 300 es

out vec4 FragColor;
in vec2 TexCoords;

uniform vec4 color;
uniform sampler2D map;
uniform bool isVertical;
uniform bool isGaussian;

vec3 gauss() {
    float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);
    vec3 tex = texture(map, TexCoords).rgb * weight[0];

    ivec2 size = textureSize(map, 0);
    vec2 tex_offset;
    tex_offset.x = 1.0 / 500.0;
    tex_offset.y = 1.0 / 300.0;
    if (!isVertical) {
        for(int i = 1; i < 5; ++i)
        {
            tex += texture(map, TexCoords + vec2(tex_offset.x * float(i), 0.0)).rgb * weight[i];
            tex += texture(map, TexCoords - vec2(tex_offset.x * float(i), 0.0)).rgb * weight[i];
        }
    } else {
        for(int i = 1; i < 5; ++i)
        {
            tex += texture(map, TexCoords + vec2(0.0, tex_offset.y * float(i))).rgb * weight[i];
            tex += texture(map, TexCoords - vec2(0.0, tex_offset.y * float(i))).rgb * weight[i];
        }
    }
    return tex;
}

void main() {
    vec3 tex;
    if (isGaussian) {
        tex = gauss();
    } else {
        tex = texture(map, TexCoords).rgb;
    }

    if (tex.r > 0.0 || tex.g > 0.0 || tex.b > 0.0) {
        FragColor.rgb = tex;
    } else {
        FragColor = color;
    }
    FragColor.a = 1.0;
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

uniform bool blinn;

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
    float spec = 0.0;

    if (blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 1.0);
    } else {
        vec3 reflectDir = reflect(-lightDir, norm);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }

    // vec3 specular = specularStrength * spec * lightColor;
    vec3 specular = vec3(0.3) * spec;
    vec3 result = (ambient + diffuse + specular) * color.xyz;
    FragColor = vec4(result, 1.0);
}
)";
