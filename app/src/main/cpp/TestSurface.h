//
// Created by yuanbin on 19-8-9.
//

#pragma once

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include <mutex>
#include <thread>

#include "ILog.h"
#include "object/Cube.h"
#include "background/Background.h"

class TestSurface {

public:
    TestSurface();
    void startRenderThread(ANativeWindow* window);

    void setQua(float w, float x, float y, float z);

private:
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    EGLConfig m_config;

    ANativeWindow* aNativeWindow;

    Camera::Ptr m_camera;
    int m_width;
    int m_height;

    bool rendering = false;

    std::thread m_renderThread;
    Background::Ptr m_Background;
    Cube::Ptr m_Cube;

    glm::vec3 __up = {0, 1, 0};
    glm::vec3 __dir = {0, 0, 1};
    glm::quat m_quat;

    std::mutex m_sensor_mutex;

    void initEGL();
    void prepare();
    void update();
    void renderLoop();
    void draw();

};

extern "C" {
__attribute__((visibility("default"))) TestSurface* allocateSurface();
}
