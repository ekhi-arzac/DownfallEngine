#include "engine/dwn_component.hpp"

#include <stdexcept>
#include <algorithm>

void DwnComponent::remove_child(const std::string& tag) {
    auto it = std::remove_if(m_children.begin(), m_children.end(),
        [&tag](const std::shared_ptr<DwnComponent>& child) {
            return child->tag == tag;
        });

    if (it != m_children.end()) {
        m_children.erase(it, m_children.end());
    } else {
        throw std::runtime_error("Child component with tag " + tag + " not found.");
    }
    
}

void DwnComponent::add_child(std::shared_ptr<DwnComponent> child) {
    
    child.get()->m_transform.set_position(m_transform.getPosition());
    m_children.push_back(std::move(child));
}


void DwnComponent::update_transform() {
    this->m_transform.update();
    for (auto& child : m_children) {
        child->update_transform();
    }
}

void DwnComponent::translate(const glm::vec3& translation) {
    m_transform.translate(translation);
    update_transform();
}

