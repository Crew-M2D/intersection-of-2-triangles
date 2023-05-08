#include "InputComponent.hpp"

#include <iostream>

#include "Application.hpp"

Triangle get_triangle_values(unsigned int number) {
    std::cout << "Enter values for Triangle" << number << std::endl;
    std::cout << "Enter the coordinates of the triangle separated by a space "
                 "line by line"
              << std::endl;
    std::cout
        << "The x coordinate is in the first place, and the y is in the second"
        << std::endl;
    Triangle new_triangle;

    for (unsigned long long i = 0; i < 3; i++) {
        std::cin >> new_triangle[i].x >> new_triangle[i].y;
    }

    return new_triangle;
}

void InputComponent::on_input_process() {
    // Считываешь новые треугольники (тут чисто рандоманые значения)
    Triangle new_triangle_1 = get_triangle_values(1);
    Triangle new_triangle_2 = get_triangle_values(2);

    // Записываешь в глабольное хранилище
    global_storage.set_triangle_1(new_triangle_1);
    global_storage.set_triangle_2(new_triangle_2);
}

// ЭТО В ДАЛЬНЕЙШЕМ ПЕРЕКАЧУЕТ В ГРАФИКС
void InputComponent::on_render() {
    auto intersection = global_storage.get_intersection();
    if (intersection.empty()) {
        std::cout << "There is no intersection" << std::endl;
    } else {
        std::cout << "The following intersection points were obtained"
                  << std::endl;
        for (unsigned long long i = 0; i < intersection.size(); i++) {
            std::cout << "(" << intersection[i].x << ", " << intersection[i].y
                      << ")" << std::endl;
        }
    }
}
