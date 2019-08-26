//
// Created by yuanbin on 19-8-12.
//

#pragma once

#include <GLES3/gl3.h>

namespace CubeInfo {

    static float size = 0.3f;

    static const GLfloat vertices[] = {
        size, size, size,   1.0f, 1.0f,
        size, -size, size,  1.0f, 0.0f,
        -size, -size, size, 0.0f, 0.0f,
        -size, size, size,  0.0f, 1.0f,

        size, size, -size,   1.0f, 1.0f,
        size, -size, -size,  1.0f, 0.0f,
        -size, -size, -size, 0.0f, 0.0f,
        -size, size, -size,  0.0f, 1.0f
    };

    static unsigned int indices[] = {

            0, 4, 1,
            1, 4, 5,

            0, 1, 3,
            1, 2, 3,

            0, 4, 3,
            3, 7, 4,

            4, 7, 5,
            7, 6, 5,

            3, 7, 2,
            2, 6, 7,

            1, 2, 6,
            1, 6, 5
    };

    static const float cubeVertices[] = {
        // positions
        -size,  size, -size,
        -size, -size, -size,
         size, -size, -size,
         size, -size, -size,
         size,  size, -size,
        -size,  size, -size,

        -size, -size,  size,
        -size, -size, -size,
        -size,  size, -size,
        -size,  size, -size,
        -size,  size,  size,
        -size, -size,  size,

         size, -size, -size,
         size, -size,  size,
         size,  size,  size,
         size,  size,  size,
         size,  size, -size,
         size, -size, -size,

        -size, -size, size,
        -size,  size, size,
         size,  size, size,
         size,  size, size,
         size, -size, size,
        -size, -size, size,

        -size, size, -size,
         size, size, -size,
         size, size,  size,
         size, size,  size,
        -size, size,  size,
        -size, size, -size,

        -size, -size, -size,
        -size, -size,  size,
         size, -size, -size,
         size, -size, -size,
        -size, -size,  size,
         size, -size,  size
    };

    static const GLfloat normal_vertices[] = {
        -size, -size, -size,  0.0f,  0.0f, -1.0f,
         size, -size, -size,  0.0f,  0.0f, -1.0f,
         size,  size, -size,  0.0f,  0.0f, -1.0f,
         size,  size, -size,  0.0f,  0.0f, -1.0f,
        -size,  size, -size,  0.0f,  0.0f, -1.0f,
        -size, -size, -size,  0.0f,  0.0f, -1.0f,

        -size, -size,  size,  0.0f,  0.0f,  1.0f,
         size, -size,  size,  0.0f,  0.0f,  1.0f,
         size,  size,  size,  0.0f,  0.0f,  1.0f,
         size,  size,  size,  0.0f,  0.0f,  1.0f,
        -size,  size,  size,  0.0f,  0.0f,  1.0f,
        -size, -size,  size,  0.0f,  0.0f,  1.0f,

        -size,  size,  size, -1.0f,  0.0f,  0.0f,
        -size,  size, -size, -1.0f,  0.0f,  0.0f,
        -size, -size, -size, -1.0f,  0.0f,  0.0f,
        -size, -size, -size, -1.0f,  0.0f,  0.0f,
        -size, -size,  size, -1.0f,  0.0f,  0.0f,
        -size,  size,  size, -1.0f,  0.0f,  0.0f,

        size,  size,  size,  1.0f,  0.0f,  0.0f,
        size,  size, -size,  1.0f,  0.0f,  0.0f,
        size, -size, -size,  1.0f,  0.0f,  0.0f,
        size, -size, -size,  1.0f,  0.0f,  0.0f,
        size, -size,  size,  1.0f,  0.0f,  0.0f,
        size,  size,  size,  1.0f,  0.0f,  0.0f,

        -size, -size, -size,  0.0f, -1.0f,  0.0f,
         size, -size, -size,  0.0f, -1.0f,  0.0f,
         size, -size,  size,  0.0f, -1.0f,  0.0f,
         size, -size,  size,  0.0f, -1.0f,  0.0f,
        -size, -size,  size,  0.0f, -1.0f,  0.0f,
        -size, -size, -size,  0.0f, -1.0f,  0.0f,

        -size,  size, -size,  0.0f,  1.0f,  0.0f,
         size,  size, -size,  0.0f,  1.0f,  0.0f,
         size,  size,  size,  0.0f,  1.0f,  0.0f,
         size,  size,  size,  0.0f,  1.0f,  0.0f,
        -size,  size,  size,  0.0f,  1.0f,  0.0f,
        -size,  size, -size,  0.0f,  1.0f,  0.0f
    };
}

