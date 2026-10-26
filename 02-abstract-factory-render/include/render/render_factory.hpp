#pragma once
#include "render/button.hpp"
#include "render/shader.hpp"
#include "render/window.hpp"

#include <memory>

class RenderFactory {
public:
    virtual ~RenderFactory() = default;
    [[nodiscard]] virtual std::unique_ptr<Window> createWindow() const = 0;
    [[nodiscard]] virtual std::unique_ptr<Button> createButton() const = 0;
    [[nodiscard]] virtual std::unique_ptr<Shader> createShader() const = 0;
};
