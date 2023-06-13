#pragma once

// #include <GLFW/glfw3.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <vector>

// Структура точки

struct Point2f {
    float x;
    float y;

    Point2f() = default;

    Point2f(float x_value, float y_value);
};

using Point = Point2f;

// Класс фигуры

class Shape {
private:
    std::vector<Point> shape_coords;

public:
    Shape() = default;

    Shape(std::initializer_list<Point> list);

    // перегрузка оператора индексации
    auto operator[](std::uint64_t index) -> Point&;
    auto operator[](std::uint64_t index) const -> const Point&;

    // добавление новой точки в конец
    void add(Point new_point);

    // сортировка
    void sort();

    // размер
    auto size() -> std::uint64_t;
    [[nodiscard]] auto size() const -> std::uint64_t;

    auto empty() -> bool;

    // получение максимального и минимального
    [[nodiscard]] auto get_max_x() const -> float;
    [[nodiscard]] auto get_min_x() const -> float;
    [[nodiscard]] auto get_max_y() const -> float;
    [[nodiscard]] auto get_min_y() const -> float;
};

class GlobalStorage {
public:
    auto get_polygon_1() -> const Shape&;
    void set_polygon_1(const Shape& polygon_1_values);

    auto get_polygon_2() -> const Shape&;
    void set_polygon_2(const Shape& polygon_2_values);

    auto get_intersection() -> const Shape&;
    void set_intersection(const Shape& intersection_values);

    auto get_ratio() -> float;
    void set_ratio(float ratio_value);

    // auto get_window() -> GLFWwindow*;
    // void set_window(GLFWwindow* window);

private:
    Shape polygon_1;
    Shape polygon_2;

    Shape intersection;

    float ratio = 1.0F;

    // GLFWwindow* window;
};

extern GlobalStorage global_storage;

class IComponent {
public:
    virtual void on_update() = 0;
    virtual void on_render() = 0;
    virtual void on_input_process() = 0;
    virtual void on_register() = 0;
    virtual void on_finish() = 0;
};

class Application {
    std::vector<IComponent*> components;

public:
    void register_component(IComponent& component);

    void run();

    auto is_running() -> bool;

private:
    void process_input();

    void update();

    void render();

    void finish();
};