//
// Created by yuanbin on 20-7-18.
//

#pragma once

#include "Object.h"

class Plane : public Object {

public:
    using Object::Object;

    void init() override ;
    void render() override ;

private:
    unsigned int VBO, VAO;
    unsigned int FBUFFERS[2];
    unsigned int FBUFFERTEXTURE[2];

    void prepareFrameBuffer(int width, int height);


};