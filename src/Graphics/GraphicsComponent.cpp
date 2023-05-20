#include <glad/glad.h>

//-------------------------------------

#include <GLFW/glfw3.h>

//-------------------------------------

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Application.hpp"
#include "GraphicsComponent.hpp"

// размеры окна
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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

class Polygon {
private:
    unsigned int VAO;  // объект Vertex Array
    unsigned int VBO;  // объекты буфера вершин
    std::array<float, 4> color;
    std::vector<float> vertices = {};

public:
    // если рисуем треугольник
    Polygon(const Triangle& triangle) {
        // заполнение вектора вершинами треугольника
        for (unsigned long long i = 0; i < 3; i++) {
            vertices.push_back(triangle[i].x);
            vertices.push_back(triangle[i].y);
            vertices.push_back(0.F);
        }
    }
    // если рисуем пересечение
    Polygon(const Intersection& intersection) {
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            vertices.push_back(intersection[i].x);
            vertices.push_back(intersection[i].y);
            vertices.push_back(0.F);
        }
    }
    void scaling_of_vertices(float max_value, float min_value) {
        float ratio = global_storage.get_ratio();
        // масштабируем координаты треугольниуов
        for (unsigned long long i = 0; i < vertices.size() / 3; i++) {
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
                     static_cast<long long>(vertices.size()) *
                         static_cast<long long>(sizeof(float)),
                     vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void*)0);
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

void GraphicsComponent::on_render() {
    // ИНЦИЛИЗАЦИЯ И НАСТРОЙКА GLFW
    glfwInit();
    // используем версию 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // используем CORE profile = используем только современные функции
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // -------------------------------------------------------
    // СОЗДАНИЕ ОКНА GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                          "Intersection of 2 triangles", 0, 0);
    // ошибка если окно не получилось создать
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    // добавляем окно в текущий контекст
    glfwMakeContextCurrent(window);

    // -------------------------------------------------------
    // НАСТРОЙКА OpenGl
    gladLoadGL();

    glViewport(0, 0, 800, 800);

    // -------------------------------------------------------
    // ВЕРШИННЫЙ И ФРАГМЕНТНЫЙ ШЕЙДЕРНЫЕ ОБЪЕКТЫ
    // вершинный
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // прикрепляем источник вершинного шейдера к объекту вершинного шейдера
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // компилируем вершинный шейдер в машинный код
    glCompileShader(vertexShader);

    // фрагментный
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // прикрепляем источник фрагментного шейдера к объекту фрагментного шейдера
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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
    // ПОЛИГОНЫ ДЛЯ ОТРИСОВКИ

    // получаем треугольники и пересечение из глобального хранилища
    Triangle triangle_1_coords = global_storage.get_triangle_1();
    Triangle triangle_2_coords = global_storage.get_triangle_2();
    Intersection intersection_coords = global_storage.get_intersection();

    // создаем полигоны
    Polygon triangle_1(triangle_1_coords);
    Polygon triangle_2(triangle_2_coords);
    Polygon intersection(intersection_coords);

    // не забываем отмасштабировать их
    float max_value = std::max(get_max_x(triangle_1_coords, triangle_2_coords),
                               get_max_y(triangle_1_coords, triangle_2_coords));
    float min_value = std::min(get_min_x(triangle_1_coords, triangle_2_coords),
                               get_min_y(triangle_1_coords, triangle_2_coords));
    triangle_1.scaling_of_vertices(max_value, min_value);
    triangle_2.scaling_of_vertices(max_value, min_value);
    intersection.scaling_of_vertices(max_value, min_value);

    // -------------------------------------------------------
    // НАСТРОЙКА КОНТЕЙНЕРОВ ДЛЯ VAO и VBO
    triangle_1.setup_VAO_VBO();
    triangle_2.setup_VAO_VBO();
    intersection.setup_VAO_VBO();

    // -------------------------------------------------------
    // ЦВЕТА
    triangle_1.set_color(1.0F, 1.0F, 0.0F, 0.25F);     // желтый
    triangle_2.set_color(0.0F, 1.0F, 1.0F, 0.25F);     // голубой
    intersection.set_color(0.0F, 1.0F, 0.24F, 0.25F);  // зеленый

    // -------------------------------------------------------
    // ИНЦИЛИЗИРУЕМ ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glUseProgram(shaderProgram);

    // -------------------------------------------------------
    // ЦИКЛ РЕНДЕРИНГА
    while (!glfwWindowShouldClose(window)) {
        // цвет фона
        glClearColor(0.5F, 0.5F, 0.5F, 1.F);
        // очистка прошлого буфера и присвоение ему нового цвета
        glClear(GL_COLOR_BUFFER_BIT);

        // сообщаем ImGui что начинается новый кадр
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glUseProgram(shaderProgram);

        triangle_1.draw();
        triangle_2.draw();
        intersection.draw();
        intersection.draw_points();

        // ОКНО С ИНФОРМАЦИЕЙ О ПЕРЕСЕЧЕНИИ
        ImGui::Begin("Intersection points");
        // текст
        if (intersection_coords.size() == 0) {
            ImGui::Text("There are no points of intersection:");
        } else {
            ImGui::Text("There are %d points of intersection:\n",
                        static_cast<int>(intersection_coords.size()));
            for (unsigned long long i = 0; i < intersection_coords.size();
                 i++) {
                ImGui::Text("%d point:\n%f %f", static_cast<int>(i+1),
                            intersection_coords[i].x, intersection_coords[i].y);
            }
        }
        //
        ImGui::End();

        // РЕНДЕР ЭЛЕМЕНТОВ ImGui
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // обновление экрана
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    // -------------------------------------------------------
    // УДАЛЯЕМ ВСЕ ОБЪЕКТЫ, ЧТО МЫ СОЗДАЛИ

    // удаляю все экземпляры ImGui
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    // удаляю созданные вершинные объекты
    triangle_1.delete_VAO_VBO();
    triangle_2.delete_VAO_VBO();
    intersection.delete_VAO_VBO();
    // удаляю шейдерную программу
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}