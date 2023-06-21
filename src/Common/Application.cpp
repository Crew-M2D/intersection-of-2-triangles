#include "Application.hpp"

#include <algorithm>
#include <array>
#include <vector>
#include <iostream>

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

void Shape::del_last() { shape_coords.pop_back(); }

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

auto GlobalStorage::get_polygon_1() const -> const Shape& { return polygon_1; }
auto GlobalStorage::get_polygon_1() -> Shape& { return polygon_1; }

void GlobalStorage::set_polygon_1(const Shape& polygon_1_values) {
    polygon_1 = polygon_1_values;
}

auto GlobalStorage::get_polygon_2() const -> const Shape& { return polygon_2; }
auto GlobalStorage::get_polygon_2() -> Shape& { return polygon_2; }

void GlobalStorage::set_polygon_2(const Shape& polygon_2_values) {
    polygon_2 = polygon_2_values;
}

auto GlobalStorage::get_intersection() -> const Shape& { return intersection; }

void GlobalStorage::set_intersection(const Shape& intersection_values) {
    intersection = intersection_values;
}

auto GlobalStorage::get_ratio() -> float { return ratio; }

void GlobalStorage::set_ratio(float ratio_value) { ratio = ratio_value; }

void GlobalStorage::create_window() {
    // СОЗДАНИЕ ОКНА GLFW
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                              "Intersection of 2 triangles", nullptr, nullptr);
    // ошибка если окно не получилось создать
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    // добавляем окно в текущий контекст
    glfwMakeContextCurrent(window);
}

auto GlobalStorage::get_window() -> GLFWwindow* { return window; }

void GlobalStorage::update_window() { glfwSwapBuffers(window); }

// class Application

Application::Application() {
    // ИНЦИЛИЗАЦИЯ И НАСТРОЙКА GLFW
    glfwInit();
    // используем версию 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // используем CORE profile = используем только современные функции
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // СОЗДАНИЕ ОКНА
    global_storage.create_window();
}

void Application::register_component(IComponent& component) {
    component.on_register();
    components.push_back(&component);
}

void Application::run() {
    std::cout<<"is run"<<std::endl;
    while (is_running()) {
        process_input();
        std::cout<<"process input"<<std::endl;
        update();
        std::cout<<"update"<<std::endl;
        render();
        std::cout<<"render"<<std::endl;
    }
    finish();
}

auto Application::is_running() -> bool {
    return glfwWindowShouldClose(global_storage.get_window()) == 0;
}

void Application::process_input() {
    for (auto& component : components) {
        component->on_input_process();
    }
}

void Application::update() {
    for (auto& component : components) {
        try {
            component->on_update();
        } catch (const std::exception& ex) {
            std::cerr << "something went wrong on processing component" << std::endl;
            std::cerr<< ex.what() << std::endl;
        } catch(...) {
            std::cerr << "something went wrong on processing component" << std::endl;
        }
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
