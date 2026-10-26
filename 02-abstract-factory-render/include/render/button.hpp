#pragma once
#include <string>

class Button {
public:
    virtual ~Button() = default;
    virtual void draw() const = 0;
    [[nodiscard]] virtual std::string platform() const = 0;
};
