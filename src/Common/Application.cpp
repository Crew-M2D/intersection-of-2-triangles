#include "Application.hpp"

#include <array>
#include <vector>

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

void Application::register_component(IComponent&& component) {
    component.on_register();
    components.push_back(&component);
}

void Application::run() {
    while (is_running()) {
        process_input();
        update();
        render();
    }
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