#include "render/factory_registry.hpp"
#include "render/opengl_factory.hpp"
#include "render/render_factory.hpp"
#include "render/vulkan_factory.hpp"

#include <gtest/gtest.h>

TEST(RenderFactoryTest, OpenGLFamilyConsistency) {
    const std::unique_ptr<RenderFactory> factory = std::make_unique<OpenGLFactory>();
    const auto window = factory->createWindow();
    const auto button = factory->createButton();
    const auto shader = factory->createShader();

    ASSERT_NE(window, nullptr);
    ASSERT_NE(button, nullptr);
    ASSERT_NE(shader, nullptr);

    EXPECT_EQ(window->platform(), "OpenGL");
    EXPECT_EQ(button->platform(), "OpenGL");
    EXPECT_EQ(shader->platform(), "OpenGL");
}

TEST(RenderFactoryTest, VulkanFamilyConsistency) {
    const std::unique_ptr<RenderFactory> factory = std::make_unique<VulkanFactory>();
    const auto window = factory->createWindow();
    const auto button = factory->createButton();
    const auto shader = factory->createShader();

    ASSERT_NE(window, nullptr);
    ASSERT_NE(button, nullptr);
    ASSERT_NE(shader, nullptr);

    EXPECT_EQ(window->platform(), "Vulkan");
    EXPECT_EQ(button->platform(), "Vulkan");
    EXPECT_EQ(shader->platform(), "Vulkan");
}

TEST(RenderFactoryTest, RuntimeFactoryReassignment) {
    std::unique_ptr<RenderFactory> factory = std::make_unique<OpenGLFactory>();
    const auto glWindow = factory->createWindow();
    EXPECT_EQ(glWindow->platform(), "OpenGL");

    // Switch factory at runtime
    factory = std::make_unique<VulkanFactory>();
    const auto vkShader = factory->createShader();
    EXPECT_EQ(vkShader->platform(), "Vulkan");

    // Previously created object remains intact and retains OpenGL identity
    EXPECT_EQ(glWindow->platform(), "OpenGL");
}

TEST(RenderFactoryTest, RegistryLookupAndUnknownThrows) {
    const auto glFactory = FactoryRegistry::create("opengl");
    ASSERT_NE(glFactory, nullptr);
    const auto glBtn = glFactory->createButton();
    EXPECT_EQ(glBtn->platform(), "OpenGL");

    const auto vkFactory = FactoryRegistry::create("vulkan");
    ASSERT_NE(vkFactory, nullptr);
    const auto vkBtn = vkFactory->createButton();
    EXPECT_EQ(vkBtn->platform(), "Vulkan");

    EXPECT_THROW(static_cast<void>(FactoryRegistry::create("directx")), std::out_of_range);
}
