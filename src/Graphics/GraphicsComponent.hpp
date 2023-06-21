#pragma once

#include <Application.hpp>

class GraphicsComponent : public IComponent {
public:
    void on_input_process() override {}

    void on_update() override {}

    void on_render() override;

    void on_register() override;

    void on_finish() override;
};