#pragma once

#include "math/dwn_transform.hpp"
#include <string>
#include <vector>
#include <memory>

class DwnComponent {
public:
    DwnComponent(const std::string& tag) : tag(tag), m_transform() {}
    virtual ~DwnComponent() = default;
    const DwnTransform& get_transform() const { return m_transform; }
    
    void add_child(std::unique_ptr<DwnComponent> child);
    void remove_child(const std::string& tag);
    void update_transform();

    void translate(const glm::vec3& translation);

    
    
private:
    const std::string tag;
    DwnTransform m_transform;
    // unique pts to the child components
    std::vector<std::unique_ptr<DwnComponent>> m_children;
};