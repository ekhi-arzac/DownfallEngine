#pragma once

#include "engine/resources/dwn_resource_manager.hpp"

#include "engine/dwn_object.hpp"
#include "engine/dwn_camera.hpp"
#include "engine/dwn_shader.hpp"
#include "engine/dwn_mesh.hpp"
#include "engine/dwn_material.hpp"
#include <unordered_map>

class DwnScene {
    public:
        DwnScene(const std::string& file_path);
        
        std::shared_ptr<DwnObject>& get_root() { return m_root; }
        const std::shared_ptr<DwnObject>& get_root() const { return m_root; }
        
    private:
        void parse_scene_file(const std::string& file_data);
        void parse_resources_section(std::istringstream& stream);
        void parse_objects_section(std::istringstream& stream);
        std::shared_ptr<DwnObject> parse_object(std::istringstream& stream);
        void parse_transform(std::istringstream& stream, DwnComponent& component);
        
        std::shared_ptr<DwnObject> m_root;

        DwnResourceManager<DwnMesh> &m_mesh_manager;
        DwnResourceManager<DwnShader> &m_shader_manager;
};