#pragma once
#include <string>

class Shader {
public:
    virtual ~Shader() = default;
    virtual void compile() const = 0;
    [[nodiscard]] virtual std::string platform() const = 0;
};
