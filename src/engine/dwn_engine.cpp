#include "engine/dwn_engine.hpp"

#include <stdexcept>

DwnEngine::DwnEngine(const std::string &title, uint32_t width, uint32_t height) : m_window(title, width, height)
{
    m_delta_time = 0.0f;
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
    m_ui.initialize(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void DwnEngine::run()
{   
    // get the current time
    double last_time = glfwGetTime();
    
    while (!glfwWindowShouldClose(m_window.get())) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Add ImGui demo window for testing
        ImGui::ShowDemoWindow();
        
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it)
        ImGuiIO& io = ImGui::GetIO();

        // Swap front and back buffers
        glfwSwapBuffers(m_window.get());

        // Poll for and process events
        glfwPollEvents();
        
        // Calculate delta time
        double current_time = glfwGetTime();
        m_delta_time = current_time - last_time;
        last_time = current_time;
        m_frames_per_second = static_cast<uint32_t>(1.0 / m_delta_time);
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
