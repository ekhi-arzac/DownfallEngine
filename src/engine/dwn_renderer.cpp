#include "engine/dwn_renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "dwn_renderer.hpp"

DwnRenderer& DwnRenderer::instance() {
    static DwnRenderer instance;
    return instance;
}

void DwnRenderer::initialize() {
    // Initialize OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    std::cout << "Renderer initialized" << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
}

void DwnRenderer::set_active_scene(std::unique_ptr<DwnScene> scene) {
    m_active_scene = std::move(scene);
}

void DwnRenderer::begin_scene(const DwnCamera &camera)
{
    m_view_projection_matrix = camera.get_view_projection_matrix();
    
    // Clear the screen
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_render_queue.clear();
}

void DwnRenderer::end_scene() {
    flush();
}

void DwnRenderer::submit(const std::shared_ptr<DwnObject>& object) {
    m_render_queue.push_back(object);
}

void DwnRenderer::flush() {
    // Process all objects in the render queue
    for (const auto& object : m_render_queue) {
        // Get the mesh, material, and shader for this object
        auto mesh = object->get_mesh();
        auto material = object->get_material();
        auto shader = object->get_shader();
        
        if (!mesh || !shader) {
            continue;
        }
        
        // Bind the shader program
        shader->bind();
        
        // Set matrices in the shader
        shader->set_uniform("u_view_projection", m_view_projection_matrix);
        shader->set_uniform("u_model", object->get_transform().get_model_matrix());
        
        // Set material properties if the object has a material
        if (material) {
            shader->set_uniform("u_material.shininess", material->shininess);
            shader->set_uniform("u_material.ambient", material->ambient_color);
            shader->set_uniform("u_material.diffuse", material->diffuse_color);
            shader->set_uniform("u_material.specular", material->specular_color);
        }
        
        // Bind the mesh
        mesh->bind();
        
        // Draw the mesh using our optimized draw method
        mesh->draw();
        
        // Unbind everything
        mesh->unbind();
        shader->unbind();
    }
    
    // Clear the render queue after processing
    m_render_queue.clear();
}

void DwnRenderer::set_clear_color(const glm::vec4& color) {
    m_clear_color = color;
}

void DwnRenderer::set_viewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void DwnRenderer::enable_depth_test(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void DwnRenderer::enable_blending(bool enable) {
    if (enable) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}

void DwnRenderer::enable_face_culling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }
}