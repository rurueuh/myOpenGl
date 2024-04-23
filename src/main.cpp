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
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const std::vector<float> verticesCube = {
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

static void openMap(std::vector<std::shared_ptr<Object>> &objects, const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }
    std::string line;
    int y = 0;
    while (std::getline(file, line))
    {
        int x = 0;
        for (const auto &c : line)
        {
            if (c == '1')
            {
                std::shared_ptr<Object> object = std::make_shared<Object>(verticesCube);
                object->move(Vector3<float>(x, 0, y));
                objects.push_back(object);
            }
            x++;
        }
        y++;
    }
}

static bool checkMove(const std::vector<std::shared_ptr<Object>> &objects, const Vector3<float> &position)
{
    for (const auto &object : objects)
    {
        if (object->pointIsInObject(position))
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    std::srand(std::time(NULL));
    Ruru::Window window(1920, 1080, "Hello World");
    window.setFramerateLimit(99999);
    window.setCursorVisible(false);
    
    std::vector<std::shared_ptr<Object>> objects;
    Object objectTest(verticesCube);
    objectTest.move(Vector3<float>(0, 0, 0));
    Object objectTest2(verticesCube);
    objectTest2.move(Vector3<float>(0, 0, 3));
    openMap(objects, "./map.txt");
    Texture texture("./wall.jpg");

    Shader shader("./shader.vs", "./shader.fs");
    Shader shader2("./shader.vs", "./shader.fs");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

    // CAMERA
    Camera camera(glm::vec3(1.0f, 0.0f, -1.0f));
    float cameraSpeed = 0.05f;

    std::vector<double> fpsList;

    while (!window.shouldClose() && Ruru::Key::isPressed(256) != GLFW_PRESS)
    {
        window.clear();
        shader.setMat4("model", model);
        view = camera.GetViewMatrix();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.use();
        for (const auto &object : objects)
            object->draw(shader, texture);
        static float timeSum = 0;
        auto time = window.getRenderTime();
        timeSum += time;
        double fps = 1.0 / time;
        if (timeSum > 60)
        {
            break;
        }
        fpsList.push_back(fps);
        if (Ruru::Key::isPressed(GLFW_KEY_D) == GLFW_PRESS)
        {
            Vector3<float> newPos = camera.Position + cameraSpeed * camera.Right;
            if (!checkMove(objects, newPos))
                camera.Position += cameraSpeed * camera.Right;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_A) == GLFW_PRESS)
        {
            Vector3<float> newPos = camera.Position - cameraSpeed * camera.Right;
            if (!checkMove(objects, newPos))
                camera.Position -= cameraSpeed * camera.Right;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_W) == GLFW_PRESS)
        {
            Vector3<float> newPos = camera.Position + cameraSpeed * camera.Front;
            if (!checkMove(objects, newPos))
                camera.Position += cameraSpeed * camera.Front;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_S) == GLFW_PRESS)
        {
            Vector3<float> newPos = camera.Position - cameraSpeed * camera.Front;
            if (!checkMove(objects, newPos))
                camera.Position -= cameraSpeed * camera.Front;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            camera.Position += cameraSpeed * camera.Up;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            camera.Position -= cameraSpeed * camera.Up;
        }
        if (Ruru::Key::isPressed(GLFW_KEY_R) == GLFW_PRESS)
        {
            camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);
        }
        if (Ruru::Key::isPressed(GLFW_KEY_F) == GLFW_PRESS)
        {
            camera.Position = glm::vec3(0.0f, 0.0f, -3.0f);
        }
        camera.ProcessMouseMovement(window);

        window.draw();
    }

    double sum = 0;
    for (const auto &fps : fpsList)
    {
        sum += fps;
    }
    printf("Average FPS: %f\n", sum / fpsList.size());

    return 0;
}
