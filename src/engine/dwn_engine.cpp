#include "engine/dwn_engine.hpp"

#include <stdexcept>

DwnEngine::DwnEngine(const std::string &title, uint32_t width, uint32_t height) : m_window(title, width, height)
{

}



DwnEngine::~DwnEngine()
{
}

void DwnEngine::initialize()
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    m_window.initialize();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void DwnEngine::run()
{
    while (!glfwWindowShouldClose(m_window.get())) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(m_window.get());

        // Poll for and process events
        glfwPollEvents();
    }
}

void DwnEngine::set_keyboard_callback(GLFWkeyfun callback)
{
    glfwSetKeyCallback(m_window.get(), callback);
}

void DwnEngine::set_mouse_callback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(m_window.get(), callback);
}
