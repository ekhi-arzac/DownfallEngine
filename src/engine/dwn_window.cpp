#include "engine/dwn_window.hpp"
#include <stdexcept>

DwnWindow::DwnWindow(const std::string &title, uint32_t width, uint32_t height) : m_width(width), m_height(height), m_title(title), m_window(nullptr, [](GLFWwindow* window) {
    if (window) {
        glfwDestroyWindow(window);
    }
}) {}

DwnWindow::~DwnWindow() {
    // TODO : Implement destructor logic if needed
}

void DwnWindow::initialize()
{
    // we take for granted that glfwInit() has been called before this function
    if (m_window.get() != nullptr) {
        throw std::runtime_error("Window already initialized");
    }

    // set hints for OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MacOS compatibility

    m_window = std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>(
        glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr),
        [](GLFWwindow* window) {
            if (window) {
                glfwDestroyWindow(window);
            }
        }
    );
    
    if (!m_window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    glfwMakeContextCurrent(m_window.get());
}

GLFWwindow *DwnWindow::get() const
{
    return m_window.get();
}
