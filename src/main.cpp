#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#include "Window.hpp"
#include "Key.hpp"
#include "Color.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

int main(int argc, char **argv)
{
    std::srand(std::time(NULL));
    Ruru::Window window(1920, 1080, "Hello World");
    window.setFramerateLimit(240);
    std::array<float, 24> vertices = {
        // positions        // colors
         0.3f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom right
        -0.3f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 1.0f,  // top
    };
    std::array<float, 24> vertices2 = {
        // positions        // colors
         0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // bottom right
        -0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.3f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 1.0f,  // top
    };
    Triangle triangle(vertices);
    Triangle triangle2(vertices2);
    Texture texture("./wall.jpg");
    Texture texture2("./test.jpg");


    Shader shader("./shader.vs", "./shader.fs");
    while (!window.shouldClose() && Ruru::Key::isPressed(256) != GLFW_PRESS)
    {
        window.clear();
        shader.use();
        triangle.draw(shader, texture);
        triangle2.draw(shader, texture2);
        if (Ruru::Key::isPressed(GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            triangle[0] += 0.01f;
            triangle[8] += 0.01f;
            triangle[16] += 0.01f;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            triangle[0] -= 0.01f;
            triangle[8] -= 0.01f;
            triangle[16] -= 0.01f;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_UP) == true) {
            triangle[1] += 0.01f;
            triangle[9] += 0.01f;
            triangle[17] += 0.01f;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_DOWN) == true) {
            triangle[1] -= 0.01f;
            triangle[9] -= 0.01f;
            triangle[17] -= 0.01f;
        }

        window.draw();
    }

    return 0;
}
