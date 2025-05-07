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
    
    void add_child(std::shared_ptr<DwnComponent> child);
    void remove_child(const std::string& tag);
    void update_transform();

    void translate(const glm::vec3& translation);

    void set_has_mesh(bool has_mesh) { m_has_mesh = has_mesh; }
    
private:
    const std::string tag;
    bool m_has_mesh = false;
    DwnTransform m_transform;
    // unique pts to the child components
    std::vector<std::shared_ptr<DwnComponent>> m_children;
    // ptr to parent component

};