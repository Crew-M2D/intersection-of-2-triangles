#include <Application.hpp>
#include <GraphicsComponent.hpp>
#include <InputComponent.hpp>
#include <MathComponent.hpp>
#include <iostream>

int main() {
    // НЕ ТРОГАТЬ КОММЕНТАРИИ
    // std::cout << "Entrypoint run" << std::endl;
    // Application app;
    // app.run();
    // app.register_component(InputComponent());
    // app.register_component(MathComponent());
    // GraphicsComponent g;
    // g.run();
    // как сделаю графику все поправлю и все сделаю

    InputComponent input_output;
    GraphicsComponent graphics_component;
    MathComponent math;
    input_output.on_input_process();
    math.on_update();
    input_output.on_render();
    graphics_component.on_render();
    return 0;
}
