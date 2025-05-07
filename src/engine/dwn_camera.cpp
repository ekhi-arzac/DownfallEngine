#include "engine/dwn_camera.hpp"

glm::mat4 DwnCamera::get_view_matrix() const
{
    glm::mat4 view = glm::lookAt(m_position, m_position + m_forward, m_up);
    return view * glm::scale(glm::mat4(1.0f), m_scale);
}