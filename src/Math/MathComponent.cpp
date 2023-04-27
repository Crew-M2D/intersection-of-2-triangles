#include "MathComponent.hpp"

#include <iostream>

auto MathComponent::calculate_intersection(Triangle triangle_1,
                                           Triangle triangle_2)
    -> Intersection {
    // алгоритм здесь
    // заместо этих двух строк
    (void)triangle_1;
    (void)triangle_2;

    return {};
}

auto MathComponent::calculate_ratio(Triangle triangle_1, Triangle triangle_2)
    -> float {
    // алгорим по нахождению коэффа здесь
    // заместо этих двух строк
    (void)triangle_1;
    (void)triangle_2;

    return 1.F;
}


void MathComponent::on_update() {
    // Считываешь треугольники из глобального хранилища
    auto triangle_1 = global_storage.get_triangle_1();
    auto triangle_2 = global_storage.get_triangle_2();
    // Находишь точки пересечения
    auto processed_intersection =
        calculate_intersection(triangle_1, triangle_2);
    // Записываешь в глобальное хранилище
    global_storage.set_intersection(processed_intersection);
    // Находишь множитель
    float processed_ratio = calculate_ratio(triangle_1, triangle_2);
    // Записываем в глабальное хранилище
    global_storage.set_ratio(processed_ratio);
}
