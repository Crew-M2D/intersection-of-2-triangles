#pragma once
#include <array>
#include <Application.hpp>

class InputComponent : public IComponent {
public:
    void on_input_process() override;

    void on_update() override {}

    void on_render() override;

    void on_register() override {}
};