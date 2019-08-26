//
// Created by yuanbin on 19-8-26.
//

#pragma once

#include "Object.h"

class Circle : public Object{

public:
    using Object::Object;

    void init() override;
    void render() override;

private:
    unsigned int VBO, VAO;

    float m_r = 0.5;
    int m_count = 200; //分割份数


};