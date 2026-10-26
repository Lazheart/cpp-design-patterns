#pragma once
#include "render/button.hpp"
#include "render/shader.hpp"
#include "render/window.hpp"

#include <iostream>

class VulkanWindow final : public Window {
public:
    void draw() const override {
        std::cout << "[Vulkan] Dibujando ventana con VkSurface\n";
    }
    [[nodiscard]] std::string platform() const override {
        return "Vulkan";
    }
};

class VulkanButton final : public Button {
public:
    void draw() const override {
        std::cout << "[Vulkan] Dibujando boton con pipeline de Vulkan\n";
    }
    [[nodiscard]] std::string platform() const override {
        return "Vulkan";
    }
};

class VulkanShader final : public Shader {
public:
    void compile() const override {
        std::cout << "[Vulkan] Compilando shader a SPIR-V\n";
    }
    [[nodiscard]] std::string platform() const override {
        return "Vulkan";
    }
};
