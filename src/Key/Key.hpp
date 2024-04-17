#pragma once

#include <GLFW/glfw3.h>

namespace Ruru
{
    namespace KeyCode
    {
        enum KeyCode
        {
            SPACE = 32,
            APOSTROPHE = 39,
            COMMA = 44,
            MINUS = 45,
            PERIOD = 46,
            SLASH = 47,
            ZERO = 48,
            ONE = 49,
            TWO = 50,
            THREE = 51,
            FOUR = 52,
            FIVE = 53,
            SIX = 54,
            SEVEN = 55,
            EIGHT = 56,
            NINE = 57,
            SEMICOLON = 59,
            EQUAL = 61,
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,
            LEFT_BRACKET = 91,
            BACKSLASH = 92,
            RIGHT_BRACKET = 93,
            GRAVE_ACCENT = 96,
            WORLD_1 = 161,
            WORLD_2 = 162,
            ESCAPE = 256,
            ENTER = 257,
            TAB = 258,
            BACKSPACE = 259,
            INSERT = 260,
            DELETE = 261,
            RIGHT = 262,
            LEFT = 263,
            DOWN = 264,
            UP = 265,
        };
    }
    class Key
    {
    public:
        using KeyCode = Ruru::KeyCode::KeyCode;
        template <typename T>
        static bool isPressed(const T &key, const Window &window)
        {
            return glfwGetKey(window, key) == GLFW_PRESS;
        }
        template <typename T>
        static bool isPressed(const T &key)
        {
            auto window = glfwGetCurrentContext();
            return glfwGetKey(window, key) == GLFW_PRESS;
        }
    private:
        uint16_t key;
    };
};