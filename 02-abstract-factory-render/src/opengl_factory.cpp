#include "render/opengl_factory.hpp"
#include "opengl_products.hpp"

std::unique_ptr<Window> OpenGLFactory::createWindow() const {
    return std::make_unique<OpenGLWindow>();
}

std::unique_ptr<Button> OpenGLFactory::createButton() const {
    return std::make_unique<OpenGLButton>();
}

std::unique_ptr<Shader> OpenGLFactory::createShader() const {
    return std::make_unique<OpenGLShader>();
}
