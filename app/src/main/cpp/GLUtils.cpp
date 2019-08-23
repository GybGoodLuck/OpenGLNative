//
// Created by yuanbin on 19-8-12.
//

#include "GLUtils.h"

GLint createProgram(const char* vShader, const char* fShader) {
    auto vertexShader = loadShader(GL_VERTEX_SHADER, vShader);
    if (!vertexShader) {
        return 0;
    }

    auto pixelShader = loadShader(GL_FRAGMENT_SHADER, fShader);
    if (!pixelShader) {
        return 0;
    }

    auto program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
    }

    return program;
}

GLint loadShader(GLenum shaderType, const char *pSource) {
    auto shader = glCreateShader(shaderType);

    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
    }

    return shader;
}