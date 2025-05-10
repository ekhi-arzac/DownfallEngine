#pragma once

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "engine/dwn_object.hpp"
#include "engine/dwn_camera.hpp"
#include "engine/dwn_shader.hpp"

class DwnRenderer {
public:
    static DwnRenderer& instance();
    
    void initialize();
    void begin_scene(const DwnCamera& camera);
    void end_scene();
    
    void submit(const std::shared_ptr<DwnObject>& object);
    void flush();
    
    void set_clear_color(const glm::vec4& color);
    void set_viewport(int x, int y, int width, int height);
    
    void enable_depth_test(bool enable = true);
    void enable_blending(bool enable = true);
    void enable_face_culling(bool enable = true);
    
private:
    DwnRenderer() = default;
    ~DwnRenderer() = default;
    DwnRenderer(const DwnRenderer&) = delete;
    DwnRenderer& operator=(const DwnRenderer&) = delete;
    DwnRenderer(DwnRenderer&&) = delete;
    DwnRenderer& operator=(DwnRenderer&&) = delete;
    
    std::vector<std::shared_ptr<DwnObject>> m_render_queue;
    glm::mat4 m_view_projection_matrix;
    glm::vec4 m_clear_color{0.1f, 0.1f, 0.1f, 1.0f};
};