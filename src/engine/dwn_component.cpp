#include "engine/dwn_component.hpp"

#include <stdexcept>

void DwnComponent::remove_child(const std::string& tag) {
    auto it = std::remove_if(m_children.begin(), m_children.end(), [&tag](const std::unique_ptr<DwnComponent>& child) {
        return child->tag == tag;
    });

    if (it == m_children.end()) {
        throw std::runtime_error("Child component with tag " + tag + " not found");
    }

    it->get()->m_transform.remove(m_transform); // Remove the transform of the child from the parent, in case someone else will use it

    m_children.erase(it, m_children.end());
}

void DwnComponent::add_child(DwnComponent& child) {
    
    child.m_transform.add(m_transform);
    m_children.push_back(std::make_unique<DwnComponent>(child));
}


void DwnComponent::update_transform() {
    for (const auto& child : m_children) {
        child->m_transform.update();
    }
}

void DwnComponent::translate(const glm::vec3& translation) {
    m_transform.translate(translation);
    update_transform();
}

