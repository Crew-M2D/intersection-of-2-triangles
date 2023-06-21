#include <glad/glad.h>

//-------------------------------------

#include <GLFW/glfw3.h>

//-------------------------------------

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Application.hpp"
#include "GraphicsComponent.hpp"

// программный шейдерный объект
GLuint shaderProgram;

// Vertex Shader source code
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// Fragment Shader source code
const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = color;\n"
    "}\n\0";

auto find_maximum_value(const Shape& polygon_1, const Shape& polygon_2)
    -> float {
    return std::max({polygon_1.get_max_x(), polygon_1.get_max_y(),
                     polygon_2.get_max_x(), polygon_2.get_max_y()});
}

auto find_minimum_value(const Shape& polygon_1, const Shape& polygon_2)
    -> float {
    return std::min({polygon_1.get_min_x(), polygon_1.get_min_y(),
                     polygon_2.get_min_x(), polygon_2.get_min_y()});
}

class Polygon {
private:
    unsigned int VAO;  // объект Vertex Array
    unsigned int VBO;  // объекты буфера вершин
    std::array<float, 4> color;

    // полигон состоит из всех возможных треугольников
    std::vector<float> vertices = {};

public:
    // конструктор по умолчанию
    Polygon() = default;
    // деструктор по умолчанию
    ~Polygon() = default;
    //
    void update_polygon(const Shape& shape) {
        vertices.clear();
        // заполнение вектора вершинами треугольника
        for (std::atomic_uint64_t i = 0; i < shape.size(); i++) {
            vertices.push_back(shape[i].x);
            vertices.push_back(shape[i].y);
            vertices.push_back(0.F);
        }
    }
    void scaling_of_vertices(float max_value, float min_value) {
        float ratio = global_storage.get_ratio();
        // масштабируем координаты
        for (std::uint64_t i = 0; i < vertices.size() / 3; i++) {
            vertices[i * 3] =
                (vertices[i * 3] - (max_value + min_value) / 2.0F) * ratio;
            vertices[1 + (i * 3)] =
                (vertices[1 + (i * 3)] - (max_value + min_value) / 2.0F) *
                ratio;
        }
    }
    void setup_VAO_VBO() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     static_cast<std::int64_t>(vertices.size()) *
                         static_cast<std::int64_t>(sizeof(float)),
                     vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
    void set_color(float r, float g, float b, float a) {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = a;
    }
    void draw() {
        glBindVertexArray(VAO);
        glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0],
                    color[1], color[2], color[3]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0,
                     static_cast<int>(vertices.size() / 3));
    }
    void draw_points() {
        glBindVertexArray(VAO);
        glUniform4f(glGetUniformLocation(shaderProgram, "color"), 0.F, 0.F, 0.F,
                    1.F);
        glDrawArrays(GL_POINTS, 0, static_cast<int>(vertices.size() / 3));
    }
    void delete_VAO_VBO() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

// два полигона и их пересечение
Polygon polygon_1;
Polygon polygon_2;
Polygon intersection;

void GraphicsComponent::on_register() {
    // -------------------------------------------------------
    // ВЕРШИННЫЙ И ФРАГМЕНТНЫЙ ШЕЙДЕРНЫЕ ОБЪЕКТЫ
    // вершинный
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // прикрепляем источник вершинного шейдера к объекту вершинного шейдера
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // компилируем вершинный шейдер в машинный код
    glCompileShader(vertexShader);

    // фрагментный
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // прикрепляем источник фрагментного шейдера к объекту фрагментного шейдера
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    // компилируем фрагментный шейдер в машинный код
    glCompileShader(fragmentShader);

    //-------------------------------------------------------
    // ШЕЙДЕРНЫЙ ПРОГРАММНЫЙ ОБЪЕКТ
    shaderProgram = glCreateProgram();
    // прикрепляем вершинный и фрагментный шейдерные объекты
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // связывание всех шейдеров вместе в шейдерный программный объект
    glLinkProgram(shaderProgram);

    // удаляем вершинный и фрагментный шейдерные объекты
    // теперь они бесполезны
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // -------------------------------------------------------
    // НАСТРОЙКА КОНТЕЙНЕРОВ ДЛЯ VAO и VBO
    polygon_1.setup_VAO_VBO();
    polygon_2.setup_VAO_VBO();
    intersection.setup_VAO_VBO();

    // -------------------------------------------------------
    // ЦВЕТА
    polygon_1.set_color(1.0F, 1.0F, 0.0F, 0.25F);      // желтый
    polygon_2.set_color(0.0F, 1.0F, 1.0F, 0.25F);      // голубой
    intersection.set_color(0.0F, 1.0F, 0.24F, 0.25F);  // зеленый
}

void GraphicsComponent::on_render() {
    std::cout << "graphics on render" << std::endl;
    // -------------------------------------------------------
    // ОБНОВЛЯЕМ ПОЛИГОНЫ ДЛЯ ОТРИСОВКИ

    // получаем полигоны и пересечение из глобального хранилища
    Shape polygon_1_coords = global_storage.get_polygon_1();
    Shape polygon_2_coords = global_storage.get_polygon_2();
    Shape intersection_coords = global_storage.get_intersection();

    // обновляем полигоны и пересечение
    polygon_1.update_polygon(polygon_1_coords);
    polygon_2.update_polygon(polygon_2_coords);
    intersection.update_polygon(intersection_coords);

    // не забываем отмасштабировать их
    float max_value = find_maximum_value(polygon_1_coords, polygon_2_coords);
    float min_value = find_minimum_value(polygon_1_coords, polygon_2_coords);
    polygon_1.scaling_of_vertices(max_value, min_value);
    polygon_2.scaling_of_vertices(max_value, min_value);
    intersection.scaling_of_vertices(max_value, min_value);

    // -------------------------------------------------------

    glUseProgram(shaderProgram);

    polygon_1.draw();
    std::cout << "polygon1 draw" << std::endl;
    polygon_2.draw();
    std::cout << "polygon2 draw" << std::endl;
    intersection.draw();
    std::cout << "intersection draw" << std::endl;
    intersection.draw_points();

    // ОКНО С ИНФОРМАЦИЕЙ О ПЕРЕСЕЧЕНИИ
    ImGui::Begin("Intersection points");
    // текст
    if (intersection_coords.size() == 0) {
        ImGui::Text("There are no points of intersection:");
    } else {
        ImGui::Text("There are %d points of intersection:\n",
                    static_cast<int>(intersection_coords.size()));
        for (std::uint64_t i = 0; i < intersection_coords.size(); i++) {
            ImGui::Text("%d point:\n%f %f", static_cast<int>(i + 1),
                        intersection_coords[i].x, intersection_coords[i].y);
        }
    }
    //
    ImGui::End();

    // РЕНДЕР ЭЛЕМЕНТОВ ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // обновление экрана
    global_storage.update_window();

    glfwPollEvents();
}

void GraphicsComponent::on_finish() {
    // УДАЛЯЕМ ВСЕ ОБЪЕКТЫ, ЧТО МЫ СОЗДАЛИ

    // удаляю созданные вершинные объекты
    polygon_1.delete_VAO_VBO();
    polygon_2.delete_VAO_VBO();
    intersection.delete_VAO_VBO();
    // удаляю шейдерную программу
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}