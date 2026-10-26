#pragma once
#include "render/button.hpp"
#include "render/shader.hpp"
#include "render/window.hpp"

#include <iostream>

class OpenGLWindow final : public Window {
public:
    void draw() const override {
        std::cout << "[OpenGL] Dibujando ventana con contexto GL\n";
    }
    [[nodiscard]] std::string platform() const override {
        return "OpenGL";
    }
};

class OpenGLButton final : public Button {
public:
    void draw() const override {
        std::cout << "[OpenGL] Dibujando boton con glDrawElements\n";
    }
    [[nodiscard]] std::string platform() const override {
        return "OpenGL";
    }
};

class OpenGLShader final : public Shader {
public:
    void compile() const override {
        std::cout << "[OpenGL] Compilando shader GLSL\n";
    }
    [[nodiscard]] std::string platform() const override {
        return "OpenGL";
    }
};
