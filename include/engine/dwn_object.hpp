#include <engine/dwn_component.hpp>
#include <engine/dwn_mesh.hpp>
#include <engine/dwn_texture.hpp>

class DwnObject : public DwnComponent {
private:
    std::shared_ptr<DwnMesh> m_mesh;
    std::shared_ptr<DwnTexture> m_texture;
    bool m_is_visible = true;
};