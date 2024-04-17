#pragma once
#include <cstdint>

namespace Ruru
{
    class Color
    {
    public:
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            : r(r), g(g), b(b), a(a) {}
        Color(uint32_t color)
            : r((color >> 0) & 0xFF), g((color >> 8) & 0xFF), b((color >> 16) & 0xFF), a((color >> 24) & 0xFF) {}
        Color(const Color &color) = default;
        ~Color() = default;

        uint8_t getR() const { return r; }
        uint8_t getG() const { return g; }
        uint8_t getB() const { return b; }
        uint8_t getA() const { return a; }

        void setR(uint8_t r) { this->r = r; }
        void setG(uint8_t g) { this->g = g; }
        void setB(uint8_t b) { this->b = b; }
        void setA(uint8_t a) { this->a = a; }
        template <typename T>
        void setColor(T r, T g, T b, T a = 255)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
        template <typename T>
        void setColor(T color)
        {
            r = (color >> 0) & 0xFF;
            g = (color >> 8) & 0xFF;
            b = (color >> 16) & 0xFF;
            a = (color >> 24) & 0xFF;
        }

        operator uint32_t() const
        {
            return (a << 24) | (b << 16) | (g << 8) | r;
        }
        auto operator==(const Color &color) const
        {
            return r == color.r && g == color.g && b == color.b && a == color.a;
        }
        auto operator!=(const Color &color) const
        {
            return !(*this == color);
        }

        uint8_t r, g, b, a;
    protected:
    private:
    };
};
inline std::ostream &operator<<(std::ostream &os, const Ruru::Color &color)
{
    os << "Color(" << (int)color.getR() << ", " << (int)color.getG() << ", " << (int)color.getB() << ", " << (int)color.getA() << ")";
    return os;
}
