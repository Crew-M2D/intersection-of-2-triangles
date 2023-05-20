#pragma once

#include <Application.hpp>

// Переопределяем только тот метод, который пишем
// on_register - функция, которая вызывается
// единожды при запуске
// оn_input_proccess() - запись
// координат on_update() - алгоритм нахождения пересечения
// on_render() - рисуем пересечение и треугольники

class MathComponent : public IComponent {
private:
    auto calculate_ratio(Triangle triangle_1, Triangle triangle_2) -> float;

public:

    auto calculate_intersection(Triangle triangle_1, Triangle triangle_2)
        -> Intersection;

    void on_update() override;

    void on_render() override {}

    void on_input_process() override {}

    void on_register() override {}

    void on_finish() override {}

    virtual ~MathComponent() {}
};