//
// Created by yuanbin on 19-8-12.
//

#pragma once

#include <memory>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include "../Camera.h"
#include "../Light.h"

class Object {

public:
    using Ptr = std::shared_ptr<Object>;

    Object(int width, int height, const glm::vec3& pos,
            const glm::vec3 &color, float alpha, const Camera::Ptr& camera);
    virtual ~Object() {}

    virtual void init() = 0;
    virtual void render() = 0;

    void updatePos();
    void scale();
    void updateRenderData();
    void updateCamera();

    void setPos(const glm::vec3& pos) {
        m_pos = pos;
    };

    glm::vec3 getPos() const {
        return m_pos;
    }

    void setColor(const glm::vec3& color) {
        m_color = color;
    }

    glm::quat getQua() const {
        return m_qua;
    }

    void setQua(const glm::quat& quat) {
        m_qua = quat;
    }

    glm::vec3 getColor() const {
        return m_color;
    }

    void setAlpha(float alpha) {
        m_alpha = alpha;
    }

    float getAlpha() const {
        return m_alpha;
    }

    void setScale(glm::vec3 scale) {
        m_scale = scale;
    }

    glm::vec3 getScale() {
        return m_scale;
    }

protected:
    int m_width;
    int m_height;

    Camera::Ptr m_camera;
    glm::vec3 m_pos;
    glm::quat m_qua = {0, 0, 0, 1};
    glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};
    glm::vec3 m_color;
    float m_alpha;

    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_transform;

    GLint s_projection;
    GLint s_view;
    GLint s_transform;
    GLint s_color;

    GLint m_program;
};

class LightObject : public Object {

public:
    LightObject(int width, int height, const glm::vec3& pos,
                const glm::vec3 &color, float alpha,
                const Camera::Ptr& camera, const Light::Ptr& light);

    virtual ~LightObject() {}

    void init() override {};
    void render() override {};

    void updateLight();

protected:
    GLint s_light_pos;
    GLint s_light_color;

    GLint s_camera_pos;

    Light::Ptr m_light;
};