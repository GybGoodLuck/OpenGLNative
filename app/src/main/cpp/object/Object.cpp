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
    m_program = (GLuint)createProgram(vertexShader, fragmentShader);
    s_projection = glGetUniformLocation(m_program, "projection");
    s_view = glGetUniformLocation(m_program, "view");
    s_transform = glGetUniformLocation(m_program, "transform");
    s_color = glGetUniformLocation(m_program, "color");
}

void Object::updatePos() {
    m_transform = glm::translate(m_transform, m_pos);
}

void Object::scale() {
    m_transform = glm::scale(m_transform, m_scale);
}

void Object::updateCamera() {
    auto projection = m_camera->getCameraProjection();

    m_projection = glm::perspective(projection.m_fov, projection.m_aspect,
                                    projection.m_zNear, projection.m_zFar);

    auto info = m_camera->getCameraInfo();
    m_view = glm::lookAt(info.m_pos, info.m_pos + info.m_dir, info.m_up);
}

void Object::updateRenderData() {
    m_transform = glm::mat4();
    updatePos();
    m_transform = m_transform * glm::mat4_cast(m_qua);
    scale();
    updateCamera();
    glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(s_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
    glUniform4f(s_color, m_color[0], m_color[1], m_color[2], m_alpha);
}

LightObject::LightObject(int width, int height, const glm::vec3 &pos, const glm::vec3 &color,
                         float alpha, const Camera::Ptr &camera, const Light::Ptr &light)
                         : Object(width, height, pos, color, alpha, camera), m_light(light) {
    m_program = (GLuint)createProgram(lightVertexShader, lightFragmentShader);
    s_projection = glGetUniformLocation(m_program, "projection");
    s_view = glGetUniformLocation(m_program, "view");
    s_transform = glGetUniformLocation(m_program, "transform");
    s_color = glGetUniformLocation(m_program, "color");

    s_light_pos = glGetUniformLocation(m_program, "lightPos");
    s_light_color = glGetUniformLocation(m_program, "lightColor");

    s_camera_pos = glGetUniformLocation(m_program, "cameraPos");
}

void LightObject::updateLight() {
    auto lightPos = m_light->getPos();
    auto lightColor = m_light->getColor();
    auto cameraPos = m_camera->getCameraInfo().m_pos;
    glUniform3f(s_light_pos, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(s_light_color, lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(s_camera_pos, cameraPos.x, cameraPos.y, cameraPos.z);
}