#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#include "Window/Window.hpp"
#include "Key/Key.hpp"
#include "Color.hpp"
#include "Triangle.hpp"
#include "Square.hpp"
#include "Shader.hpp"

int main(int argc, char **argv)
{
    std::srand(std::time(NULL));
    Ruru::Window window(800, 600, "Hello World");
    window.setFramerateLimit(240);

    Triangle triangle({
        // positions        // colors
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f    // top

    });

    Shader shader("./shader.vs", "./shader.fs");
    while (!window.shouldClose() && Ruru::Key::isPressed(256) != GLFW_PRESS)
    {
        window.clear();
        shader.use();
        float timeValue = glfwGetTime();
        {
            float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
            triangle[3] = greenValue;
            triangle[4] = 1.0f - greenValue;
        }
        {
            float redValue = (std::sin(timeValue) / 2.0f) + 0.5f;
            triangle[10] = redValue;
            triangle[11] = 1.0f - redValue;
        }
        {
            float blueValue = (std::sin(timeValue) / 2.0f) + 0.5f;
            triangle[17] = blueValue;
            triangle[18] = 1.0f - blueValue;
        }
        {
            float blueValue = (std::sin(timeValue)) + 0.0f;
            triangle[1] = 0.0f - blueValue;
            triangle[6] = 0.0f - blueValue;
            triangle[12] = 0.0f - blueValue;
        }
        triangle.draw(shader);

        window.draw();
    }

    return 0;
}
