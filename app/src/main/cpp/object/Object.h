//
// Created by yuanbin on 19-8-12.
//

#pragma once

#include <memory>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include "../Camera.h"

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

    void getShaderParams();

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

protected:
    int m_width;
    int m_height;

    Camera::Ptr m_camera;
    glm::vec3 m_pos;
    glm::quat m_qua = {0.707, 0, 0.707, 0};
    float m_scale = 1.0f;
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