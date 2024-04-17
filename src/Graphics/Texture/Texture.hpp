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
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        static bool first = true;
        if (first) {
            first = false;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_set_flip_vertically_on_load(true);
        }
        data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
            if (nrChannels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else if (nrChannels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            else if (nrChannels == 1)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            else
                throw std::runtime_error("Unsupported number of channels");
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            throw std::runtime_error("Failed to load texture");
        }
        stbi_image_free(data);
        this->unbind();
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