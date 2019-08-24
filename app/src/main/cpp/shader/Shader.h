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

