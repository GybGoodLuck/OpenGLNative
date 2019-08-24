//
// Created by yuanbin on 19-8-24.
//

#include "Background.h"
#include "BackgroundVertices.h"

#include "../shader/Shader.h"
#include "../GLUtils.h"
#include "../TexttureLoader.h"

Background::Background(int width, int height, const Camera::Ptr &camera) : m_camera(camera) {

    m_program = createProgram(BGVertexShader, BGFragmentShader);

    glViewport(0, 0, width, height);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BackgroundVertices), BackgroundVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    loadTexture();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    m_transform = glm::translate(m_transform, {0, 0, 0});
    m_transform = glm::rotate(m_transform, glm::radians(90.f), {0, 1, 0});
    m_transform = glm::rotate(m_transform, -glm::radians(90.f), {1, 0, 0});
    m_transform = glm::scale(m_transform, {55.0f, 55.0f, 55.0f});
    getShaderParams();
}

void Background::loadTexture() {

    std::string bottom ("/system/iris/skybox/bottom.jpg");
    std::string back ("/system/iris/skybox/back.jpg");
    std::string front ("/system/iris/skybox/front.jpg");
    std::string left ("/system/iris/skybox/left.jpg");
    std::string right ("/system/iris/skybox/right.jpg");
    std::string top ("/system/iris/skybox/top.jpg");

    faces.push_back(right);
    faces.push_back(left);
    faces.push_back(top);
    faces.push_back(bottom);
    faces.push_back(front);
    faces.push_back(back);

    auto textureID  = loadCubemap(faces);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void Background::getShaderParams() {
    s_projection =  glGetUniformLocation(m_program, "projection");
    s_view = glGetUniformLocation(m_program, "view");
    s_transform = glGetUniformLocation(m_program, "transform");
}

void Background::updateCamera() {
    auto projection = m_camera->getCameraProjection();

    m_projection = glm::perspective(projection.m_fov, projection.m_aspect,
                                    projection.m_zNear, projection.m_zFar);

    auto info = m_camera->getCameraInfo();
    m_view = glm::lookAt(info.m_pos, info.m_pos + info.m_dir, info.m_up);
}

void Background::updateRenderData() {
    updateCamera();
    glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(s_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
}

void Background::render() {
    glUseProgram(m_program);
    updateRenderData();
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}