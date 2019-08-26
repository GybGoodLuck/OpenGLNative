//
// Created by yuanbin on 19-8-26.
//

#include "Circle.h"

#include "../ILog.h"
#include "../shape/CubeInfo.h"

void Circle::init() {
    float* vertices = new float[m_count * 3];
    float delta = static_cast<float>(2.0 * M_PI / m_count);

    for (int i = 0; i < m_count * 3;) {
        vertices[i] = m_r * cos(delta * i);     // x
        vertices[i + 1] = m_r * sin(delta * i); // y
        vertices[i + 2] = 0.5f;                 // z
        i = i + 3;
    }

    glViewport(0, 0, m_width, m_height);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * m_count, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Circle::render() {
    glUseProgram(m_program);
    updateRenderData();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_count);
    glBindVertexArray(0);
}