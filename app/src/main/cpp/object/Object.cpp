//
// Created by yuanbin on 19-8-12.
//

#include "Object.h"
#include "../shader/Shader.h"
#include "../GLUtils.h"
#include "../ILog.h"

Object::Object(int width, int height, const glm::vec3 &pos,
        const glm::vec3 &color, float alpha, const Camera::Ptr &camera)
        : m_width(width), m_height(height), m_pos(pos),
          m_color(color), m_alpha(alpha), m_camera(camera) {
    updatePos(m_pos);
    m_program = createProgram(vertexShader, fragmentShader);
    getShaderParams();
}

void Object::updatePos(const glm::vec3& pos) {
    m_transform = glm::translate(m_transform, pos);
}

void Object::scale(float scale) {
    m_transform = glm::scale(m_transform, {scale, scale, scale});
}

void Object::rotate(const glm::vec3& axis, float radians) {
    m_transform = glm::rotate(m_transform, radians, axis);
}

void Object::getShaderParams() {
    s_projection =  glGetUniformLocation(m_program, "projection");
    s_view = glGetUniformLocation(m_program, "view");
    s_transform = glGetUniformLocation(m_program, "transform");
    s_color = glGetUniformLocation(m_program, "color");
}

void Object::updateCamera() {
    auto projection = m_camera->getCameraProjection();

    m_projection = glm::perspective(projection.m_fov, projection.m_aspect,
                                    projection.m_zNear, projection.m_zFar);

    auto info = m_camera->getCameraInfo();
    m_view = glm::lookAt(info.m_pos, info.m_pos + info.m_dir, info.m_up);
}

void Object::updateRenderData() {
    updateCamera();
    glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(s_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
    glUniform4f(s_color, m_color[0], m_color[1], m_color[2], m_alpha);
}