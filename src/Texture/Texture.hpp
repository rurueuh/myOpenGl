#pragma once

#include <GL/glew.h>

#include <array>
#include <GLFW/glfw3.h>
#include "stb_image.h"

class Texture
{
public:
    Texture(const char *path)
    {
        data = stbi_load(path, &width, &height, &nrChannels, 0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            throw std::runtime_error("Failed to load texture");
        }
        stbi_image_free(data);
    }
    ~Texture() { glDeleteTextures(1, &texture); }

    void bind() {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    operator unsigned int() const { return texture; }

protected:
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char *data;
};