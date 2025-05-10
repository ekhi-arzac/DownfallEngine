#include "math/dwn_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include "dwn_transform.hpp"

void DwnTransform::update()
{
    // Update the forward, up, and right vectors based on the rotation
    glm::mat4 rotationMatrix = glm::yawPitchRoll(glm::radians(m_rotation.y), glm::radians(m_rotation.x), glm::radians(m_rotation.z));
    m_forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
    m_up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    m_right = glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
}

void DwnTransform::translate(const glm::vec3 &translation)
{
    m_position += translation.x * m_right + translation.y * m_up + translation.z * m_forward;
}

void DwnTransform::add(const DwnTransform &transform)
{
    m_position += transform.m_position;
    m_rotation += transform.m_rotation;
    m_scale *= transform.m_scale;
    update();
}

void DwnTransform::remove(const DwnTransform &transform)
{
    m_position -= transform.m_position;
    m_rotation -= transform.m_rotation;
    m_scale /= transform.m_scale;
    update();
}

const glm::mat4 &DwnTransform::get_model_matrix() const
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), m_right);
    model = glm::rotate(model, glm::radians(m_rotation.y), m_up);
    model = glm::rotate(model, glm::radians(m_rotation.z), m_forward);
    model = glm::scale(model, m_scale);
    return model;
}
const glm::mat4 &DwnTransform::get_view_matrix() const
{
    glm::mat4 view = glm::lookAt(m_position, m_position + m_forward, m_up);
    const auto result = view * glm::scale(glm::mat4(1.0f), m_scale);
    return result;
}