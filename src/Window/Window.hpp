#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include "Color.hpp"

namespace Ruru {
    class Window {
    public:
        Window(uint16_t width, uint16_t height, const char *title);
        Window(uint16_t width, uint16_t height, const std::string &title);
        ~Window();

        void draw();
        bool shouldClose();
        double getRenderTime() {
            auto time = glfwGetTime();
            glfwSetTime(0);
            return time;
        }
        void setFramerateLimit(uint32_t limit) { frameRateLimit = limit; }

        void clear() { glClear(GL_COLOR_BUFFER_BIT); }
        void clear(const Ruru::Color &color) {
            glClearColor(color.getR() / 255.0f, color.getG() / 255.0f, color.getB() / 255.0f, color.getA() / 255.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        operator GLFWwindow *() const { return window; }

        class Exception : public std::runtime_error {
        public:
            Exception(const std::string &msg) : std::runtime_error(msg) {}
        };

    protected:
        GLFWwindow *window;

        u_int16_t width, height;
        uint32_t frameRateLimit = -1;
        std::string title;

        void initWindow();
    };
};