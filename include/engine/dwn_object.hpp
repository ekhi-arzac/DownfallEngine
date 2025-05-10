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

        std::shared_ptr<DwnMesh> get_mesh() const {
            return m_mesh;
        }
        std::shared_ptr<DwnShader> get_shader() const {
            return m_shader;
        }
        std::shared_ptr<DwnTexture> get_texture() const {
            return m_texture;
        }
        std::shared_ptr<DwnMaterial> get_material() const {
            return m_material;
        }





private:
    std::shared_ptr<DwnMesh> m_mesh;
    std::shared_ptr<DwnTexture> m_texture;
    std::shared_ptr<DwnShader> m_shader;
    std::shared_ptr<DwnMaterial> m_material;
    bool m_is_visible = true;
};