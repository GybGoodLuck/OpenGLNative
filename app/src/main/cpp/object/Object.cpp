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
    m_light_program = createProgram(lightVertexShader, lightFragmentShader);
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
    light_projection =  glGetUniformLocation(m_light_program, "projection");
    light_view = glGetUniformLocation(m_light_program, "view");
    light_transform = glGetUniformLocation(m_light_program, "transform");
    light_color = glGetUniformLocation(m_light_program, "color");

    s_obj_color = glGetUniformLocation(m_program, "objectColor");
    s_light_color = glGetUniformLocation(m_program, "lightColor");
    s_light_pos = glGetUniformLocation(m_program, "lightPos");
    s_view_pos = glGetUniformLocation(m_program, "viewPos");
    s_projection = glGetUniformLocation(m_program, "projection");
    s_view = glGetUniformLocation(m_program, "view");
    s_transform = glGetUniformLocation(m_program, "transform");
}

void Object::updateLight() {
    glUseProgram(m_light_program);
    glUniformMatrix4fv(light_projection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(light_view, 1, GL_FALSE, glm::value_ptr(m_view));
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, {1.0f, 1.0f, 2.0f});
    model = glm::scale(model, glm::vec3(0.2f));
    glUniformMatrix4fv(light_transform, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(light_color, 1.0, 1.0, 1.0, 1.0);
}

void Object::updateRenderData() {
    glUseProgram(m_program);
    glUniform3f(s_obj_color, m_color[0], m_color[1], m_color[2]);
    glUniform3f(s_light_color, 0.6f, 0.5f, 0.8f);
    glUniform3f(s_light_pos, 1.0f, 1.0f, 2.0f);
    auto viewPos = m_camera->getCameraInfo().m_pos;
    glUniform3f(s_view_pos, viewPos.x, viewPos.y, viewPos.z);

    glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(s_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
}