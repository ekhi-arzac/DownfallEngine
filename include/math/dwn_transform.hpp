#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class DwnTransform {
private:
    glm::vec3 m_position;
    glm::vec3 m_rotation; // Euler angles in degrees
    glm::vec3 m_scale;

    glm::vec3 m_forward;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
public:
    DwnTransform() : m_position(0.0f), m_rotation(0.0f), m_scale(1.0f), m_forward(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f), m_right(1.0f, 0.0f, 0.0f), m_world_up(0.0f, 1.0f, 0.0f) {}
    ~DwnTransform() = default;

    void set_position(const glm::vec3& position) { m_position = position; }
    void set_rotation(const glm::vec3& rotation) { m_rotation = rotation; }
    void set_scale(const glm::vec3& scale) { m_scale = scale; }

    const glm::vec3& getPosition() const { return m_position; }
    const glm::vec3& getRotation() const { return m_rotation; }
    const glm::vec3& getScale() const { return m_scale; }

    void update();
    void translate(const glm::vec3& translation);
    void add(const DwnTransform& transform);
    void remove(const DwnTransform& transform);
    const glm::mat4& get_model_matrix() const;
    const glm::mat4& get_view_matrix() const;

};