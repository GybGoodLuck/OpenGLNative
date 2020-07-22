//
// Created by yuanbin on 20-7-18.
//

#include "../ILog.h"
#include "Plane.h"

static const float planeVertices[] = {
    // positions
    -1.f,  1.f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     1.f,  1.f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -1.f, -1.f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    -1.f, -1.f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     1.f, -1.f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     1.f,  1.f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
};

void Plane::init() {
//    glViewport(0, 0, m_width, m_height);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    prepareFrameBuffer(m_width, m_height);
    drawFrame = true;
}

void Plane::render() {
    int isVertical = 0;
    bool isFirst = true;
    glUseProgram(m_program);
    int isGaussian = glGetUniformLocation(m_program, "isGaussian");
    if (drawFrame) {
        glUniform1i(isGaussian, true);
        for (int i = 0; i < 12; i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, FBUFFERS[isVertical]);
            int isVerticalLocation = glGetUniformLocation(m_program, "isVertical");
            glUniform1i(isVerticalLocation, isVertical);
            if (isFirst) {
                glBindTexture(GL_TEXTURE_2D, m_textureId);
                isFirst = false;
            } else {
                glBindTexture(GL_TEXTURE_2D, FBUFFERTEXTURE[!isVertical]);
            }
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            isVertical = !isVertical;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        drawFrame = false;
    }
    glUniform1i(isGaussian, false);
    updateRenderData();
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, FBUFFERTEXTURE[0]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Plane::prepareFrameBuffer(int width, int height) {
    glGenFramebuffers(2, FBUFFERS);
    glGenTextures(2, FBUFFERTEXTURE);
    for (int i = 0; i < 2; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, FBUFFERS[i]);
        glBindTexture(GL_TEXTURE_2D, FBUFFERTEXTURE[i]);
        glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glGenerateMipmap(GL_TEXTURE_2D);
        glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBUFFERTEXTURE[i], 0
        );
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            LOGD("frame buffer not completed");
        }
    }
}
