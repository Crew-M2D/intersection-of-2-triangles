#include <glad/glad.h>

//------------------------------------

#include <GLFW/glfw3.h>

//-------------------------------------

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <string>

#include "GraphicsInputComponent.hpp"


void GraphicsInputComponent::on_register() {
    // НАСТРОЙКА OpenGl
    gladLoadGL();

    glViewport(0, 0, 800, 800);
    // ------------------------------------
    // ИНЦИЛИЗИРУЕМ ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(global_storage.get_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void input_polygon_1_window() {
    ImGui::Begin("Enter the values of polygon 1");

    ImGui::Text("Polygon 1");
    Shape& polygon1 = global_storage.get_polygon_1();
    if (ImGui::Button("Add Point")) {
        polygon1.add(Point(0.F, 0.F));
    }
    if (ImGui::Button("Delete Point")) {
        polygon1.del_last();
    }
    for (std::uint64_t i = 0; i < polygon1.size(); i++) {
        ImGui::Text("Point %d", static_cast<int>(i + 1));
        ImGui::SameLine();
        ImGui::SetNextItemWidth(70);
        ImGui::InputFloat(("x##" + std::to_string(i)).c_str(), &polygon1[i].x);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(70);
        ImGui::InputFloat(("y##" + std::to_string(i)).c_str(), &polygon1[i].y);
    }

    ImGui::End();
}

void input_polygon_2_window() {
    ImGui::Begin("Enter the values of polygon 2");

    ImGui::Text("Polygon 2");
    Shape& polygon2 = global_storage.get_polygon_2();
    if (ImGui::Button("Add Point")) {
        polygon2.add(Point(0.F, 0.F));
    }
    if (ImGui::Button("Delete Point")) {
        polygon2.del_last();
    }
    for (std::uint64_t i = 0; i < polygon2.size(); i++) {
        ImGui::Text("Point %d", static_cast<int>(i + 1));
        ImGui::SameLine();
        ImGui::SetNextItemWidth(70);
        ImGui::InputFloat(("x##" + std::to_string(i)).c_str(), &polygon2[i].x);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(70);
        ImGui::InputFloat(("y##" + std::to_string(i)).c_str(), &polygon2[i].y);
    }

    ImGui::End();
}

void GraphicsInputComponent::on_input_process() {
    // цвет фона
    glClearColor(0.5F, 0.5F, 0.5F, 1.F);
    // очистка прошлого буфера и присвоение ему нового цвета
    glClear(GL_COLOR_BUFFER_BIT);

    // сообщаем ImGui что начинается новый кадр
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    input_polygon_1_window();

    input_polygon_2_window();
}

void GraphicsInputComponent::on_finish() {
    // удаляю все экземпляры ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}