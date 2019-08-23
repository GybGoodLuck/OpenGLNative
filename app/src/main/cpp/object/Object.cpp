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
    updateCameraProjection(m_camera->getCameraProjection());
    updateCameraInfo(m_camera->getCameraInfo());
    m_program = createProgram(gVertexShader, gFragmentShader);
    getShaderParams();
}

void Object::updateCameraProjection(const CameraProjection &projection) {
    m_projection = glm::perspective(projection.m_fov, projection.m_aspect,
                                    projection.m_zNear, projection.m_zFar);
}

void Object::updateCameraInfo(const CameraInfo& cameraInfo) {
    m_view = glm::lookAt(cameraInfo.m_pos, cameraInfo.m_dir, cameraInfo.m_up);
}

void Object::updatePos(const glm::vec3& pos) {
    m_transform = glm::translate(m_transform, pos);
//    m_transform = glm::scale(m_transform, {0.5, 0.5, 0.5});
}

void Object::rotate(const glm::vec3& axis, float radians) {
    m_transform = glm::rotate(m_transform, radians, axis);
}

void Object::getShaderParams() {
    s_projection =  glGetUniformLocation(m_program, "projection");
    s_view = glGetUniformLocation(m_program, "view");
    s_transform = glGetUniformLocation(m_program, "transform");
    s_color = glGetUniformLocation(m_program, "color");
    glUseProgram(m_program);
}

void Object::updateRenderData() {
    glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(s_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
    glUniform4f(s_color, m_color[0], m_color[1], m_color[2], m_alpha);
}