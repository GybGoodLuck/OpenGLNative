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

class TestSurface {

public:
    TestSurface();
    void startRenderThread(ANativeWindow* window);

    void setCameraDir(float x, float y, float z);

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
    Cube::Ptr m_Cube, m_Cube2;

    GLuint mTextureID;

    void initEGL();
    void prepareTriangle();
    void renderLoop();
    void draw();

};

extern "C" {
__attribute__((visibility("default"))) TestSurface* allocateSurface();
}
