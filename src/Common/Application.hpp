#pragma once

#include <array>
#include <vector>

struct Point2f {
    float x;
    float y;

    Point2f() = default;

    Point2f(float x_value, float y_value);
};

using Point = Point2f;
using Triangle = std::array<Point, 3>;
using Intersection = std::vector<Point>;

class GlobalStorage {
public:
    auto get_triangle_1() -> const Triangle&;
    void set_triangle_1(const Triangle& triangle_1_values);

    auto get_triangle_2() -> const Triangle&;
    void set_triangle_2(const Triangle& triangle_2_values);

    auto get_intersection() -> const Intersection&;
    void set_intersection(const Intersection& intersection_values);

    auto get_ratio() -> float;
    void set_ratio(float ratio_value);

private:
    Triangle triangle_1;
    Triangle triangle_2;

    Intersection intersection;

    float ratio = 1.0F;
};

extern GlobalStorage global_storage;

class IComponent {
public:
    virtual void on_update() = 0;
    virtual void on_render() = 0;
    virtual void on_input_process() = 0;
    virtual void on_register() = 0;
};

class Application {
    std::vector<IComponent*> components;

public:
    void register_component(IComponent&& component);

    void run();

    auto is_running() -> bool;

private:
    void process_input();

    void update();

    void render();
};