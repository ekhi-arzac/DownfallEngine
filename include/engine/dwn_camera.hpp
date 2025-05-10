#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "engine/dwn_component.hpp"

class DwnCamera : public DwnComponent {
public:
    DwnCamera(const std::string& tag = "Camera") : DwnComponent(tag) {}
    virtual ~DwnCamera() = default;

    virtual void set_fov(float fov) = 0;
    virtual void set_aspect_ratio(float aspect_ratio) = 0;
    virtual void set_near_plane(float near_plane) = 0;
    virtual void set_far_plane(float far_plane) = 0;
    
    // These already exist in the DwnComponent transform
    // virtual void set_position(glm::vec3 position) = 0;
    // virtual void set_rotation(float pitch, float yaw, float roll) = 0;
    
    virtual void update() = 0;
    virtual glm::mat4 get_view_projection_matrix() const = 0;
    virtual glm::mat4 get_view_matrix() const = 0;
    virtual glm::mat4 get_projection_matrix() const = 0;
};

class DwnPerspectiveCamera : public DwnCamera {
public:
    DwnPerspectiveCamera(const std::string& tag = "PerspectiveCamera");
    ~DwnPerspectiveCamera() override = default;

    void set_fov(float fov) override;
    void set_aspect_ratio(float aspect_ratio) override;
    void set_near_plane(float near_plane) override;
    void set_far_plane(float far_plane) override;

    void update() override;
    glm::mat4 get_view_projection_matrix() const override;
    glm::mat4 get_view_matrix() const override;
    glm::mat4 get_projection_matrix() const override;

private:
    glm::mat4 m_projection_matrix;
    
    float m_fov;
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;
    float m_zoom;
};

class DwnOrthographicCamera : public DwnCamera {
public:
    DwnOrthographicCamera(const std::string& tag = "OrthographicCamera");
    ~DwnOrthographicCamera() override = default;

    void set_fov(float fov) override;
    void set_aspect_ratio(float aspect_ratio) override;
    void set_near_plane(float near_plane) override;
    void set_far_plane(float far_plane) override;
    
    void update() override;
    glm::mat4 get_view_projection_matrix() const override;
    glm::mat4 get_view_matrix() const override;
    glm::mat4 get_projection_matrix() const override;

private:
    glm::mat4 m_projection_matrix;
    
    float m_left, m_right, m_bottom, m_top;
    float m_fov;  // Not directly used but kept for interface consistency
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;
    float m_zoom;
};
