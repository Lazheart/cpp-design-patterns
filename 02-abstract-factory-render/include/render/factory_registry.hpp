#pragma once
#include "render/render_factory.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

using FactoryMaker = std::function<std::unique_ptr<RenderFactory>()>;

class FactoryRegistry {
public:
    [[nodiscard]] static const std::unordered_map<std::string, FactoryMaker>& getRegistry();
    [[nodiscard]] static std::unique_ptr<RenderFactory> create(const std::string& backendName);
};
