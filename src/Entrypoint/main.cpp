#include <Application.hpp>
#include <GraphicsComponent.hpp>
#include <GraphicsInputComponent.hpp>
#include <InputComponent.hpp>
#include <MathComponent.hpp>
#include <iostream>

auto main() -> int {
    std::cout << "main" << std::endl;
    Application app;
    std::cout << "App was created" << std::endl;

    GraphicsComponent graphics_component;
    GraphicsInputComponent input_component;
    MathComponent math_component;

    std::cout << "Before register" << std::endl;

    app.register_component(input_component);
    std::cout << "Input_component was registered" << std::endl;
    app.register_component(math_component);
    std::cout << "Math_component was registered" << std::endl;
    app.register_component(graphics_component);
    std::cout << "Graphics_component was registered" << std::endl;

    app.run();

    return 0;
}
