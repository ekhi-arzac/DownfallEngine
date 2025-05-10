#pragma once

#include <engine/dwn_component.hpp>
#include <engine/dwn_mesh.hpp>
#include <engine/dwn_texture.hpp>
#include <engine/dwn_shader.hpp>

class DwnObject : public DwnComponent {
    public:
        void set_mesh(const std::shared_ptr<DwnMesh>& mesh) {
            m_mesh = mesh;
            set_has_mesh(true);
        }

        void set_shader(const std::shared_ptr<DwnShader>& shader) {
            m_shader = shader;
        }


private:
    std::shared_ptr<DwnMesh> m_mesh;
    std::shared_ptr<DwnTexture> m_texture;
    std::shared_ptr<DwnShader> m_shader;
    bool m_is_visible = true;
};