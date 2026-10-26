#include "render/opengl_factory.hpp"
#include "render/render_factory.hpp"
#include "render/vulkan_factory.hpp"

#include <memory>

int main() {
    std::unique_ptr<RenderFactory> factory = std::make_unique<OpenGLFactory>();
    auto window = factory->createWindow();
    auto button = factory->createButton();
    window->draw();
    button->draw();

    factory = std::make_unique<VulkanFactory>();
    auto shader = factory->createShader();
    shader->compile();

    return 0;
}
