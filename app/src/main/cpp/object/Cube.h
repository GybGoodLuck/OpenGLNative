//
// Created by yuanbin on 19-8-9.
//

#pragma once

#include <android/log.h>

#include "Object.h"
#include "../ILog.h"

class Cube : public Object {

public:
    using Object::Object;

    void init() override ;
    void render() override ;

private:
    unsigned int VBO, VAO;
};
