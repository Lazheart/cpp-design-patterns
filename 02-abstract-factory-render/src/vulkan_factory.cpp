#include "render/vulkan_factory.hpp"
#include "vulkan_products.hpp"

std::unique_ptr<Window> VulkanFactory::createWindow() const {
    return std::make_unique<VulkanWindow>();
}

std::unique_ptr<Button> VulkanFactory::createButton() const {
    return std::make_unique<VulkanButton>();
}

std::unique_ptr<Shader> VulkanFactory::createShader() const {
    return std::make_unique<VulkanShader>();
}
