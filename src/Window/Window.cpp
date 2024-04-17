#include "Window.hpp"

void Ruru::Window::initWindow()
{
    if (!glfwInit()) {
        throw Exception("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw Exception("Failed to open GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) {
        throw Exception("Failed to initialize GLEW");
    }
}

Ruru::Window::Window(uint16_t width, uint16_t height, const char *title)
    : width(width), height(height), title(title)
{
    initWindow();
}

Ruru::Window::Window(uint16_t width, uint16_t height, const std::string &title)
    : width(width), height(height), title(title)
{
    initWindow();
}

Ruru::Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Ruru::Window::draw()
{
    if (frameRateLimit != -1) {
        static auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (duration < 1000 / frameRateLimit) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frameRateLimit - duration));
        }
        start = std::chrono::high_resolution_clock::now();
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Ruru::Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}
