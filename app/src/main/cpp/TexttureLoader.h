//
// Created by yuanbin on 19-8-14.
//

#pragma once

#include <vector>
#include <GLES3/gl3.h>

GLuint loadTexture(const char* path);

unsigned int loadCubemap(std::vector<std::string> faces);