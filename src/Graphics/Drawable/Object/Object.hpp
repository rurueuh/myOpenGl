#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Color.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include <vector>

constexpr int DIFF = 8;

class Object : public Drawable
{
public:
    Object(std::vector<float> vertices) : _vertices(vertices)
    {
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                                           "}\0";
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, DIFF * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, DIFF * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, DIFF * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void draw() const override
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / DIFF);
    }
    void draw(Shader &shader) const override
    {
        // todo: check last used shader id with static and use it if it is not the same ? (performance improvement)
        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / DIFF);
    }
    void draw(Shader &shader, Texture &texture) const override
    {
        // todo: check last used shader id with static and use it if it is not the same ? (performance improvement)
        shader.use();
        texture.bind();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / DIFF);
        texture.unbind();
    }

    template <typename T>
    float at(T index) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float *data = (float *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
        float result = data[index];
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return result;
    }

    bool pointIsInObject(const Vector3<float> &point) const
    {
        auto pos = this->position;

        auto point1 = _vertices[0] + pos.x;
        auto point2 = _vertices[0 + 1] - pos.y;
        auto point3 = _vertices[0 + 2] - pos.z;
        if (point.z >= point3 && point.z <= point3 + 1) {
            if (point.x >= point1 && point.x <= point1 + 1)
            {
                if (point.y >= point2 && point.y <= point2 + 1)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void move(const Vector3<float> &offset) override
    {
        position += offset;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float *data = (float *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
        for (int i = 0; i < _vertices.size(); i += DIFF)
        {
            data[i] += offset.x;
            data[i + 1] += offset.z;
            data[i + 2] += offset.y;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~Object()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }

    template <typename T>
    float &operator[](T index)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float *data = (float *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
        float &result = data[index];
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return result;
    }
    operator unsigned int() const { return VAO; }

    std::vector<float> &getVertices() { return _vertices; }

private:
    unsigned int shaderProgram;
    unsigned int VBO, VAO;
    std::vector<float> _vertices;
};