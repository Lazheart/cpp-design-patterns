#pragma once
#include <string>

class Window {
public:
    virtual ~Window() = default;
    virtual void draw() const = 0;
    [[nodiscard]] virtual std::string platform() const = 0;
};
