#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "TestSurface.h"

extern "C" JNIEXPORT void JNICALL
Java_com_iris_testdemo_MainActivity_startRenderThread(
        JNIEnv *env,
        jobject /* this */,
        jobject mSurface) {
    ANativeWindow* externalWindow = ANativeWindow_fromSurface(env, mSurface);
    TestSurface* surface = allocateSurface();
    surface->startRenderThread(externalWindow);
}

extern "C" JNIEXPORT void JNICALL
Java_com_iris_testdemo_MainActivity_setCameraDir(
        JNIEnv *env,
        jobject /* this */,
        jfloat x,
        jfloat y,
        jfloat z) {
    TestSurface* surface = allocateSurface();
    surface->setCameraDir(x, y, z);
}

extern "C" JNIEXPORT void JNICALL
Java_com_iris_testdemo_Sensor_setRotQ(
        JNIEnv *env,
        jobject /* this */,
        jfloat w,
        jfloat x,
        jfloat y,
        jfloat z) {
    TestSurface* surface = allocateSurface();
    surface->setQua(w, x, y, z);
}