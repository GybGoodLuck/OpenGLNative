//
// Created by yuanbin on 19-8-24.
//

#pragma once

#include <string>
#include <vector>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include "../Camera.h"

class Background{

public:
    using Ptr = std::shared_ptr<Background>;
    Background(int width, int height, const Camera::Ptr& camera);
    void render();

private:

    void loadTexture();
    void getShaderParams();
    void updateCamera();
    void updateRenderData();

    Camera::Ptr m_camera;

    GLint s_projection;
    GLint s_view;
    GLint s_transform;

    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_transform;

    GLint m_program;

    unsigned int VBO, VAO;

    std::vector<std::string> faces;
};
