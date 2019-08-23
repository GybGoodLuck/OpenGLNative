//
// Created by yuanbin on 19-8-9.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Cube.h"

#include "../shape/CubeInfo.h"
#include "../TexttureLoader.h"

unsigned int VBO, VAO, EBO;

std::vector<std::string> faces;

void Cube::init() {

    std::string bottom ("/system/iris/skybox/bottom.jpg");
    std::string back ("/system/iris/skybox/back.jpg");
    std::string front ("/system/iris/skybox/front.jpg");
    std::string left ("/system/iris/skybox/left.jpg");
    std::string right ("/system/iris/skybox/right.jpg");
    std::string top ("/system/iris/skybox/top.jpg");

    faces.push_back(right);
    faces.push_back(left);
    faces.push_back(top);
    faces.push_back(bottom);
    faces.push_back(front);
    faces.push_back(back);

    glViewport(0, 0, m_width, m_height);

//    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeInfo::skyboxVertices), CubeInfo::skyboxVertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeInfo::indices), CubeInfo::indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    mTextureID = loadCubemap(faces);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    rotate({1, 0, 0}, -glm::radians(90.f));
}

void Cube::render() {
    glDepthFunc(GL_LEQUAL);
    updateRenderData();
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}