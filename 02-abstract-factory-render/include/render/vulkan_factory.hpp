#pragma once
#include "render/render_factory.hpp"

class VulkanFactory final : public RenderFactory {
public:
    [[nodiscard]] std::unique_ptr<Window> createWindow() const override;
    [[nodiscard]] std::unique_ptr<Button> createButton() const override;
    [[nodiscard]] std::unique_ptr<Shader> createShader() const override;
};
