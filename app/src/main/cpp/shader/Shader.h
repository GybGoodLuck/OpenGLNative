//
// Created by yuanbin on 19-8-12.
//

#pragma once

static const char gVertexShader[] = R"(
#version 300 es
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec2 aTexCoord;

out vec3 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;
void main() {
  gl_Position = projection * view * transform * vec4(aPos, 1.0);
  TexCoord = aPos;
}
)";

static const char gFragmentShader[] = R"(
#version 300 es
out vec4 FragColor;
uniform vec4 color;

in vec3 TexCoord;
uniform samplerCube skybox;

void main() {
    FragColor = texture(skybox, TexCoord);
    FragColor.w = 1.0;
    // FragColor = {1.0, 1.0, 1.0, 1.0}
}
)";

