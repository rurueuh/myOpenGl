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
#include "Object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char **argv)
{
    std::srand(std::time(NULL));
    Ruru::Window window(1920, 1080, "Hello World");
    window.setFramerateLimit(60);
    std::array<float, 24> vertices = {
        // positions        // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 1.0f,   // top
    };
    std::array<float, 24> vertices2 = {
        // positions        // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 1.0f,   // top
    };
    std::vector<float> verticesCube = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f};
    std::vector<glm::vec3> cubesPos = {};
    for (int i = 0; i < 1000; i++)
    {
        // between -100 and 100
        cubesPos.push_back(glm::vec3((std::rand() % 200 - 100) / 10.0f, (std::rand() % 200 - 100) / 10.0f, (std::rand() % 200 - 100) / 10.0f));
    }
    cubesPos.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    Object object(verticesCube);
    Triangle triangle(vertices);
    Triangle triangle2(vertices2);
    Texture texture("./wall.jpg");
    Texture texture2("./discord.png");

    Shader shader("./shader.vs", "./shader.fs");
    Shader shader2("./shader.vs", "./shader.fs");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-75.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

    while (!window.shouldClose() && Ruru::Key::isPressed(256) != GLFW_PRESS)
    {
        window.clear();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.use();
        // triangle2.draw(shader, texture2);
        // triangle.draw(shader, texture);
        auto oldModel = model;
        for (unsigned int i = 0; i < (cubesPos.size()); i++)
        {
            model = glm::translate(model, cubesPos[i]);
            // model move random cube
            shader.setMat4("model", model);
            object.draw(shader, texture);
            model = oldModel;
        }
        model = oldModel;
        shader.setMat4("model", model);
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
        static bool autoRotate = false;
        if (Ruru::Key::isPressed(GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            autoRotate = !autoRotate;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        if (autoRotate)
        {
            model = glm::rotate(model, glm::radians(-0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_Q) == true)
        {
            model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_E) == true)
        {
            model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_W) == true)
        {
            model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_S) == true)
        {
            model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_A) == true)
        {
            model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_D) == true)
        {
            model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (Ruru::Key::isPressed(GLFW_KEY_UP) == true)
        {
            triangle[1] += 0.01f;
            triangle[9] += 0.01f;
            triangle[17] += 0.01f;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_DOWN) == true)
        {
            triangle[1] -= 0.01f;
            triangle[9] -= 0.01f;
            triangle[17] -= 0.01f;
        }

        window.draw();
    }

    return 0;
}
