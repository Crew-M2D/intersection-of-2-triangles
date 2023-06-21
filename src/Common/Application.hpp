#pragma once

#include <GLFW/glfw3.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <vector>

// размеры окна
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// Структура точки

struct Point2f {
    float x;
    float y;

    Point2f() = default;

    Point2f(float x_value, float y_value);

    ~Point2f() = default;
};

using Point = Point2f;

// Класс фигуры

class Shape {
public:
    Shape() = default;

    Shape(std::initializer_list<Point> list);

    // перегрузка оператора индексации
    auto operator[](std::uint64_t index) -> Point&;
    auto operator[](std::uint64_t index) const -> const Point&;

    // добавление новой точки в конец
    void add(Point new_point);

    void del_last();

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

private:
    std::vector<Point> shape_coords;
};

class GlobalStorage {
public:
    [[nodiscard]] auto get_polygon_1() const -> const Shape&;
    auto get_polygon_1() -> Shape&;
    void set_polygon_1(const Shape& polygon_1_values);

    [[nodiscard]] auto get_polygon_2() const -> const Shape&;
    auto get_polygon_2() -> Shape&;
    void set_polygon_2(const Shape& polygon_2_values);

    auto get_intersection() -> const Shape&;
    void set_intersection(const Shape& intersection_values);

    auto get_ratio() -> float;
    void set_ratio(float ratio_value);

    void create_window();

    auto get_window() -> GLFWwindow*;

    void update_window();

private:
    Shape polygon_1 = {Point(-5.F, 0.F), Point(0.F, 5.F), Point(5.F, 0.F)};
    Shape polygon_2 = {Point(0.F, 0.F), Point(5.F, 5.F), Point(10.F, 0.F)};

    Shape intersection;

    float ratio = 1.0F;

    GLFWwindow* window;
};

extern GlobalStorage global_storage;

// Переопределяем только тот метод, который пишем
// on_register - функция, которая вызывается
// единожды при запуске
// оn_input_proccess() - запись
// координат on_update() - алгоритм нахождения пересечения
// on_render() - рисуем пересечение и треугольники
// on_finish() - удаляем объекты и т.п.
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
    Application();

    void register_component(IComponent& component);

    void run();

    auto is_running() -> bool;

private:
    void process_input();

    void update();

    void render();

    void finish();
};