#include "engine/dwn_camera.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

// DwnPerspectiveCamera implementation
DwnPerspectiveCamera::DwnPerspectiveCamera(const std::string& tag)
    : DwnCamera(tag)
    , m_projection_matrix(1.0f)
    , m_fov(45.0f)
    , m_aspect_ratio(16.0f / 9.0f)
    , m_near_plane(0.1f)
    , m_far_plane(1000.0f)
    , m_zoom(1.0f)
{
    update();
}

void DwnPerspectiveCamera::set_fov(float fov)
{
    m_fov = fov;
    update();
}

void DwnPerspectiveCamera::set_aspect_ratio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
    update();
}

void DwnPerspectiveCamera::set_near_plane(float near_plane)
{
    m_near_plane = near_plane;
    update();
}

void DwnPerspectiveCamera::set_far_plane(float far_plane)
{
    m_far_plane = far_plane;
    update();
}

void DwnPerspectiveCamera::update()
{
    // Update the transform using the component's method
    update_transform();
    
    // Update projection matrix
    m_projection_matrix = glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near_plane, m_far_plane);
}

glm::mat4 DwnPerspectiveCamera::get_view_matrix() const
{
    return get_transform().get_view_matrix();
}

glm::mat4 DwnPerspectiveCamera::get_projection_matrix() const
{
    return m_projection_matrix;
}

glm::mat4 DwnPerspectiveCamera::get_view_projection_matrix() const
{
    return m_projection_matrix * get_view_matrix();
}

// DwnOrthographicCamera implementation
DwnOrthographicCamera::DwnOrthographicCamera(const std::string& tag)
    : DwnCamera(tag)
    , m_projection_matrix(1.0f)
    , m_left(-10.0f)
    , m_right(10.0f)
    , m_bottom(-10.0f)
    , m_top(10.0f)
    , m_fov(45.0f)
    , m_aspect_ratio(16.0f / 9.0f)
    , m_near_plane(0.1f)
    , m_far_plane(1000.0f)
    , m_zoom(1.0f)
{
    update();
}

void DwnOrthographicCamera::set_fov(float fov)
{
    m_fov = fov;
    // Use FOV to adjust the zoom factor for orthographic projection
    float zoom_factor = 45.0f / fov;
    m_left = -10.0f * zoom_factor;
    m_right = 10.0f * zoom_factor;
    m_bottom = -10.0f * zoom_factor / m_aspect_ratio;
    m_top = 10.0f * zoom_factor / m_aspect_ratio;
    update();
}

void DwnOrthographicCamera::set_aspect_ratio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
    m_bottom = m_left / aspect_ratio;
    m_top = m_right / aspect_ratio;
    update();
}

void DwnOrthographicCamera::set_near_plane(float near_plane)
{
    m_near_plane = near_plane;
    update();
}

void DwnOrthographicCamera::set_far_plane(float far_plane)
{
    m_far_plane = far_plane;
    update();
}

void DwnOrthographicCamera::update()
{
    // Update the transform using the component's method
    update_transform();
    
    // Update projection matrix
    m_projection_matrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_near_plane, m_far_plane);
}

glm::mat4 DwnOrthographicCamera::get_view_matrix() const
{
    return get_transform().get_view_matrix();
}

glm::mat4 DwnOrthographicCamera::get_projection_matrix() const
{
    return m_projection_matrix;
}

glm::mat4 DwnOrthographicCamera::get_view_projection_matrix() const
{
    return m_projection_matrix * get_view_matrix();
}
