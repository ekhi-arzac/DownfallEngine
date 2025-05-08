#pragma once

#include <imgui.h>
#include <imgui_internal.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "engine/dwn_window.hpp"

class DwnUI {
public:
    DwnUI();
    void initialize(const DwnWindow& window);
    void render();

};