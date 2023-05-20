#include "InputComponent.hpp"

#include <cstdint>
#include <cstdint>
#include <iostream>

#include "Application.hpp"

auto get_polygon_values(unsigned int number) -> Shape {
    std::cout << "Enter values for Shape" << number << std::endl;
    std::cout << "Firstly, enter the number of coordinates" << std::endl;
    std::uint64_t counter;
    std::cin >> counter;
    std::cout << "Now enter the coordinates of the triangle separated by a space "
                 "line by line"
              << std::endl;
    std::cout
        << "The x coordinate is in the first place, and the y is in the second"
        << std::endl;
    Shape new_polygon;

    float p_x;
    float p_y;
    for (std::uint64_t i = 0; i < counter; i++) {
        std::cin >> p_x >> p_y;
        new_polygon.add(Point(p_x, p_y));
    }

    return new_polygon;
}

void InputComponent::on_input_process() {
    // Новые многоугольники
    Shape new_polygon_1 = get_polygon_values(1);
    Shape new_polygon_2 = get_polygon_values(2);

    // Записываешь в глабольное хранилище
    global_storage.set_polygon_1(new_polygon_1);
    global_storage.set_polygon_2(new_polygon_2);
}

void InputComponent::on_render() {
    auto intersection = global_storage.get_intersection();
    if (intersection.empty()) {
        std::cout << "There is no intersection" << std::endl;
    } else {
        std::cout << "The following intersection points were obtained"
                  << std::endl;
        for (std::uint64_t i = 0; i < intersection.size(); i++) {
            std::cout << "(" << intersection[i].x << ", " << intersection[i].y
                      << ")" << std::endl;
        }
    }
}
