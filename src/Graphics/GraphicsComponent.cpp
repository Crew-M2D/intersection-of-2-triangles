#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <array>
#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "GraphicsComponent.hpp"

GLuint shaderProgram;
GLuint VAO, VBO, EBO;

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 0.5f);\n"
    "}\n\0";

void window_create() {
    glfwInit();
    // использу версию 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "ImGui + GLFW", NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    global_storage.set_window(window);
}

void set_shaderProgram() {
    // создаем вершинный шейдерный объект и компилируем его в машинный код
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // создаем фрагментный шейдерный объект и компилируем его в машинный код
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // создаем программный шейдерный объект
    shaderProgram = glCreateProgram();
    // присоединяем шейдеры вершин и фрагментов к программе Shader
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // нам больше не нужны вершинный и фргментный шейдерные объекты
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void initialize_ImGui() {
    // инцилизируем ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(global_storage.get_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void changes_coordinates() {}

void GraphicsComponent::on_register() {
    window_create();

    gladLoadGL();
    // видимая область
    glViewport(0, 0, 800, 800);

    set_shaderProgram();
}