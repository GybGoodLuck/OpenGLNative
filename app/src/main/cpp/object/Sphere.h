//
// Created by yuanbin on 19-8-27.
//

#pragma once

#include <vector>

#include "Object.h"

class Sphere : public LightObject {

public:
    using LightObject::LightObject;

    void init() override ;
    void render() override ;

private:

    void initVertices();

    const unsigned int X_SEGMENTS = 200;
    const unsigned int Y_SEGMENTS = 200;
    const float PI = static_cast<float>(M_PI);

    unsigned int VBO, VAO, EBO;

    std::vector<float> data;
    std::vector<unsigned int> indices;
};