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

    void updateCameraProjection(const CameraProjection& projection);
    void updateCameraInfo(const CameraInfo& cameraInfo);
    void updatePos(const glm::vec3& pos);
    void rotate(const glm::vec3& axis, float radians);
    void updateRenderData();
    void updateLight();

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
    glm::vec3 m_color;
    float m_alpha;

    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_transform;

    GLint s_projection;
    GLint s_view;
    GLint s_transform;
    GLint s_obj_color;
    GLint s_light_color;
    GLint s_light_pos;
    GLint s_view_pos;

    GLint light_projection;
    GLint light_view;
    GLint light_transform;
    GLint light_color;

    GLint m_program;
    GLint m_light_program;
};