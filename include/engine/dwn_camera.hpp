#pragma once
#include <glm/vec3.hpp>

#include "engine/dwn_component.hpp"

class DwnCamera : public DwnComponent {
public:
    DwnCamera() = default;
    virtual ~DwnCamera() = default;

    virtual void set_position(glm::vec3 position) = 0;
    virtual void set_rotation(float pitch, float yaw, float roll) = 0;
    virtual void set_fov(float fov) = 0;
    virtual void set_aspect_ratio(float aspect_ratio) = 0;
    virtual void set_near_plane(float near_plane) = 0;
    virtual void set_far_plane(float far_plane) = 0;
    virtual void update() = 0;
    virtual void get_projection_matrix() = 0;
};

class DwnPerspectiveCamera : public DwnCamera {
public:
    DwnPerspectiveCamera() = default;
    ~DwnPerspectiveCamera() override = default;

    void set_position(glm::vec3 position) override;
    void set_rotation(float pitch, float yaw, float roll) override;
    void set_fov(float fov) override;
    void set_aspect_ratio(float aspect_ratio) override;
    void set_near_plane(float near_plane) override;
    void set_far_plane(float far_plane) override;
    void get_projection_matrix() override;

    void update() override;
private:

    float m_fov;
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;
    float m_pitch;
    float m_yaw;
    float m_roll;
    float m_speed;
    float m_sensitivity;
    float m_zoom;
};

class DwnOrthographicCamera : public DwnCamera {
public:
    DwnOrthographicCamera() = default;
    ~DwnOrthographicCamera() override = default;

    void set_position(glm::vec3 position) override;
    void set_rotation(float pitch, float yaw, float roll) override;
    void set_fov(float fov) override;
    void set_aspect_ratio(float aspect_ratio) override;
    void set_near_plane(float near_plane) override;
    void set_far_plane(float far_plane) override;
    void get_projection_matrix() override;

    void update() override;
private:

    float m_fov;
    float m_aspect_ratio;
    float m_near_plane;
    float m_far_plane;
    float m_pitch;
    float m_yaw;
    float m_roll;
    float m_speed;
    float m_sensitivity;
    float m_zoom;
};
