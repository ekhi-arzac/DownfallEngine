#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>
#include <stdint.h>
class DwnWindow {

public:
    DwnWindow(const std::string& title, uint32_t width, uint32_t height);
    ~DwnWindow();

    void initialize();
    GLFWwindow* get() const;
private:
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> m_window;
    std::string m_title;
    uint32_t m_width;
    uint32_t m_height;


};