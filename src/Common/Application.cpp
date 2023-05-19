#include "Application.hpp"

#include <array>
#include <vector>
#include <algorithm>

GlobalStorage global_storage;

Point2f::Point2f(float x_value, float y_value) : x(x_value), y(y_value) {}

auto GlobalStorage::get_triangle_1() -> const Triangle& { return triangle_1; }

void GlobalStorage::set_triangle_1(const Triangle& triangle_1_values) {
    triangle_1 = triangle_1_values;
}

auto GlobalStorage::get_triangle_2() -> const Triangle& { return triangle_2; }

void GlobalStorage::set_triangle_2(const Triangle& triangle_2_values) {
    triangle_2 = triangle_2_values;
}

auto GlobalStorage::get_intersection() -> const Intersection& {
    return intersection;
}

void GlobalStorage::set_intersection(const Intersection& intersection_values) {
    intersection = intersection_values;
}

auto GlobalStorage::get_ratio() -> float { return ratio; }

void GlobalStorage::set_ratio(float ratio_value) { ratio = ratio_value; }

// void GlobalStorage::set_window(GLFWwindow* g_window) { window = g_window; }

// auto GlobalStorage::get_window() -> GLFWwindow* { return window; }

void Application::register_component(IComponent& component) {
    component.on_register();
    components.push_back(&component);
}

void Application::run() {
    while (is_running()) {
        process_input();
        update();
        render();
    }
    finish();
}

auto Application::is_running() -> bool { return true; }

void Application::process_input() {
    for (auto& component : components) {
        component->on_input_process();
    }
}

void Application::update() {
    for (auto& component : components) {
        component->on_update();
    }
}

void Application::render() {
    for (auto& component : components) {
        component->on_render();
    }
}

void Application::finish() {
    for (auto& component : components) {
        component->on_finish();
    }
}

float get_min_y(const Triangle& triangle_1, const Triangle& triangle_2) {
    return std::min({triangle_1[0].y, triangle_1[1].y, triangle_1[2].y,
                     triangle_2[0].y, triangle_2[1].y, triangle_2[2].y});
}
float get_min_x(const Triangle& triangle_1, const Triangle& triangle_2) {
    return std::min({triangle_1[0].x, triangle_1[1].x, triangle_1[2].x,
                     triangle_2[0].x, triangle_2[1].x, triangle_2[2].x});
}
float get_max_y(const Triangle& triangle_1, const Triangle& triangle_2) {
    return std::max({triangle_1[0].y, triangle_1[1].y, triangle_1[2].y,
                     triangle_2[0].y, triangle_2[1].y, triangle_2[2].y});
}
float get_max_x(const Triangle& triangle_1, const Triangle& triangle_2) {
    return std::max({triangle_1[0].x, triangle_1[1].x, triangle_1[2].x,
                     triangle_2[0].x, triangle_2[1].x, triangle_2[2].x});
}
