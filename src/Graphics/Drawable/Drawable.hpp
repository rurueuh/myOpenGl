#pragma once

#include <iostream>
#include <Vector2.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;

    virtual void draw() const = 0;
    virtual void draw(Shader& shader) const = 0;
    virtual void draw(Shader& shader, Texture& texture) const = 0;

    virtual void move(const Vector3<float>& offset) = 0;

protected:
    Vector3<float> position = {0.0f, 0.0f, 0.0f};
    Vector2<float> scale = {1.0f, 1.0f};
    float rotation = 0.0f;

    uint32_t VAO = -1;
    uint32_t VBO = -1;
};