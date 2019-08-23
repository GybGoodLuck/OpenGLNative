//
// Created by yuanbin on 19-8-12.
//

#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct CameraProjection {
    float m_fov = glm::radians(45.0f);
    float m_zNear = 0.1f;
    float m_zFar = 100.f;
    float m_aspect = 1.0f;
};

struct CameraInfo {
    glm::vec3 m_pos = { 0.0f, 0.0f, 5.0f };
    glm::vec3 m_dir = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_up = { 0.0f, 1.0f, 0.0f };
};

class Camera {

public:
    using Ptr = std::shared_ptr<Camera>;

    void setCameraInfo(const CameraInfo& info) {
        m_cameraInfo = info;
    }

    CameraInfo getCameraInfo() const {
        return m_cameraInfo;
    }

    void setCameraProjection(CameraProjection projection) {
        m_projection = projection;
    }

    CameraProjection getCameraProjection() {
        return m_projection;
    }

private:
    CameraInfo m_cameraInfo;
    CameraProjection m_projection;
};
