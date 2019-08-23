//
// Created by yuanbin on 19-8-12.
//

#pragma once

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

GLint createProgram(const char* vShader, const char* fShader);

GLint loadShader(GLenum shaderType, const char* pSource);
