#include "Application.hpp"

#include <algorithm>
#include <array>
#include <vector>

GlobalStorage global_storage;

// struct Point2f

Point2f::Point2f(float x_value, float y_value) : x(x_value), y(y_value) {}

// class Shape

Shape::Shape(std::initializer_list<Point> list) {
    for (auto x : list) {
        shape_coords.push_back(x);
    }
}

auto Shape::operator[](std::uint64_t index) -> Point& {
    if (index >= shape_coords.size()) {
        throw std::runtime_error("index out of range");
    }
    return shape_coords[index];
}

auto Shape::operator[](std::uint64_t index) const -> const Point& {
    if (index >= shape_coords.size()) {
        throw std::runtime_error("index out of range");
    }
    return shape_coords[index];
}

void Shape::add(Point new_point) { shape_coords.push_back(new_point); }

auto Shape::size() -> std::uint64_t { return shape_coords.size(); }

auto Shape::size() const -> std::uint64_t { return shape_coords.size(); }

auto Shape::empty() -> bool { return shape_coords.empty(); }

void Shape::sort() {
    std::sort(shape_coords.begin(), shape_coords.end(),
              [](Point a, Point b) { return a.x < b.x; });
    std::sort(shape_coords.begin(), shape_coords.end(), [](Point a, Point b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    });
}

auto Shape::get_max_x() const -> float {
    auto result = std::max_element(shape_coords.begin(), shape_coords.end(),
                                   [](Point a, Point b) { return a.x < b.x; });
    return result->x;
}

auto Shape::get_min_x() const -> float {
    auto result = std::min_element(shape_coords.begin(), shape_coords.end(),
                                   [](Point a, Point b) { return a.x < b.x; });
    return result->x;
}

auto Shape::get_max_y() const -> float {
    auto result = std::max_element(shape_coords.begin(), shape_coords.end(),
                                   [](Point a, Point b) { return a.y < b.y; });
    return result->y;
}

auto Shape::get_min_y() const -> float {
    auto result = std::max_element(shape_coords.begin(), shape_coords.end(),
                                   [](Point a, Point b) { return a.y < b.y; });
    return result->y;
}

// class GlobalStorage

auto GlobalStorage::get_polygon_1() -> const Shape& { return polygon_1; }

void GlobalStorage::set_polygon_1(const Shape& polygon_1_values) {
    polygon_1 = polygon_1_values;
}

auto GlobalStorage::get_polygon_2() -> const Shape& { return polygon_2; }

void GlobalStorage::set_polygon_2(const Shape& polygon_2_values) {
    polygon_2 = polygon_2_values;
}

auto GlobalStorage::get_intersection() -> const Shape& { return intersection; }

void GlobalStorage::set_intersection(const Shape& intersection_values) {
    intersection = intersection_values;
}

auto GlobalStorage::get_ratio() -> float { return ratio; }

void GlobalStorage::set_ratio(float ratio_value) { ratio = ratio_value; }

// void GlobalStorage::set_window(GLFWwindow* g_window) { window = g_window; }

// auto GlobalStorage::get_window() -> GLFWwindow* { return window; }

// class Application

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
