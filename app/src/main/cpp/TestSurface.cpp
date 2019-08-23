//
// Created by yuanbin on 19-8-9.
//

#include "TestSurface.h"
#include "TexttureLoader.h"

TestSurface::TestSurface() {
    m_camera = std::make_shared<Camera>();
}

void TestSurface::initEGL() {
    EGLint bit = EGL_OPENGL_ES2_BIT;
    EGLint configSpec[] = {
            EGL_RENDERABLE_TYPE, bit,
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_SAMPLES, 4, EGL_NONE
    };

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint eglMajVers, eglMinVers;
    EGLint numConfigs;
    eglInitialize(m_display, &eglMajVers, &eglMinVers);
    eglChooseConfig(m_display, configSpec, &m_config, 1, &numConfigs);
    m_surface = eglCreateWindowSurface(m_display, m_config, aNativeWindow, NULL);
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_height);

    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    m_context = eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, ctxAttr);
    eglMakeCurrent(m_display, m_surface, m_surface, m_context);
}

void TestSurface::startRenderThread(ANativeWindow* window) {
    aNativeWindow = window;
    rendering = true;
    m_renderThread = std::thread(std::bind(&TestSurface::renderLoop, this));
}

void TestSurface::prepareTriangle() {
    glm::vec3 pos = {0.0f, 0.0f, 0.0f};
    glm::vec3 pos2 = {0.0f, 1.0f, 0.0f};
    glm::vec3 color = {0.0f, 1.0f, 0.0f};
    glm::vec3 color2 = {1.0f, 1.0f, 1.0f};
    m_Cube = std::make_shared<Cube>(m_width, m_height, pos, color, 0.6f, m_camera);
    m_Cube->init();
    m_Cube2 = std::make_shared<Cube>(m_width, m_height, pos2, color2, 0.8f, m_camera);
//    m_Cube2->init();
}

void TestSurface::setCameraDir(float x, float y, float z) {
}

void TestSurface::setQua(float w, float x, float y, float z) {
    glm::quat quat;
    quat.w = w;
    quat.x = x;
    quat.y = y;
    quat.z = z;
    auto camerInfo = m_camera->getCameraInfo();
    camerInfo.m_dir = quat * __dir;
    camerInfo.m_up = quat * __up;
    camerInfo.m_up.y = -camerInfo.m_up.y;
    m_camera->setCameraInfo(camerInfo);
    m_Cube->updateCameraInfo(camerInfo);
}

void TestSurface::renderLoop() {
    initEGL();
    prepareTriangle();
    while (rendering) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        draw();
        eglSwapBuffers(m_display, m_surface);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void TestSurface::draw() {
    m_Cube->render();
    // m_Cube2->render();
}

TestSurface* testSurface = nullptr;
TestSurface* allocateSurface() {
    static std::mutex m_mutex;

    if (testSurface != nullptr) {
        return testSurface;
    }
    std::lock_guard<std::mutex> guard(m_mutex);
    testSurface = new TestSurface();
    return testSurface;
}

