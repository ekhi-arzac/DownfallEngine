#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include "engine/dwn_window.hpp"

class DwnEngine {
public:
    DwnEngine(const std::string &title, uint32_t width, uint32_t height);
    ~DwnEngine();

    void initialize();
    void run();

    void set_keyboard_callback(GLFWkeyfun callback);
    void set_mouse_callback(GLFWmousebuttonfun callback);

private:
    DwnWindow m_window;
};