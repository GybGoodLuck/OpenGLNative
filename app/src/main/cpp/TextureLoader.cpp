//
// Created by yuanbin on 19-8-14.
//

#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "TexttureLoader.h"
#include "ILog.h"

GLuint loadTexture(const char* path) {

    GLuint texture;

    typedef std::unique_ptr<unsigned char, std::function<void(unsigned char*)>>
            stbi_ptr;

    int w, h, n;
    stbi_set_flip_vertically_on_load(false);
    stbi_ptr data(stbi_load(path, &w, &h, &n, 0),
            [path](unsigned char* data) {
                  if (data) {
                      stbi_image_free(data);
                  } else {
                      LOGD( "failed to load at path: %s", path);
                      stbi_image_free(data);
                  }
              });
    LOGD( "loadTexture (%d %d) path: %s", w, h, path);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //线性滤图
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}


unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            LOGD( "Cubemap texture failed to load at path: %s", faces[i].c_str());
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

