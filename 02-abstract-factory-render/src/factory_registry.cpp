#include "render/factory_registry.hpp"
#include "render/opengl_factory.hpp"
#include "render/vulkan_factory.hpp"

#include <stdexcept>

const std::unordered_map<std::string, FactoryMaker>& FactoryRegistry::getRegistry() {
    static const std::unordered_map<std::string, FactoryMaker> registry = {
        {"opengl", []() -> std::unique_ptr<RenderFactory> { return std::make_unique<OpenGLFactory>(); }},
        {"vulkan", []() -> std::unique_ptr<RenderFactory> { return std::make_unique<VulkanFactory>(); }},
    };
    return registry;
}

std::unique_ptr<RenderFactory> FactoryRegistry::create(const std::string& backendName) {
    const auto& registry = getRegistry();
    auto it = registry.find(backendName);
    if (it == registry.end()) {
        throw std::out_of_range("Backend desconocido: " + backendName);
    }
    return it->second();
}
