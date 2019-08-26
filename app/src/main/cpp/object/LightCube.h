//
// Created by yuanbin on 19-8-26.
//

#pragma once

#include "Object.h"

class LightCube : public LightObject {

public:
    using LightObject::LightObject;

    void init() override ;
    void render() override ;

private:
    unsigned int VBO, VAO;
};