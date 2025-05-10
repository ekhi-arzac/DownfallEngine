#include "engine/resources/dwn_scene.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

DwnScene::DwnScene(const std::string &file_path)
    : m_mesh_manager(DwnResourceManager<DwnMesh>::instance()), 
      m_shader_manager(DwnResourceManager<DwnShader>::instance())
{
    // read the scene file
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open scene file: " + file_path);
    }
    std::string line;
    std::string scene_data;
    while (std::getline(file, line)) {
        scene_data += line + "\n";
    }
    file.close();

    // Parse the scene file
    parse_scene_file(scene_data);
}

void DwnScene::parse_scene_file(const std::string& file_data)
{
    std::istringstream stream(file_data);
    std::string token;
    
    while (stream >> token) {
        if (token == "resources") {
            parse_resources_section(stream);
        } else if (token == "objects") {
            parse_objects_section(stream);
        } else {
            std::cerr << "Unknown section: " << token << std::endl;
            // Skip to the next line
            std::getline(stream, token);
        }
    }
}

void DwnScene::parse_resources_section(std::istringstream& stream)
{
    std::string token;
    
    while (stream >> token) {
        if (token == "end") {
            return;
        } else if (token == "mesh") {
            std::string tag_keyword, tag_value;
            std::string file_keyword, file_value;
            
            stream >> tag_keyword;
            if (tag_keyword != "tag") {
                throw std::runtime_error("Expected 'tag' keyword for mesh");
            }
            
            stream >> tag_value;
            // Remove quotes
            tag_value = tag_value.substr(1, tag_value.size() - 2);
            
            stream >> file_keyword;
            if (file_keyword != "file") {
                throw std::runtime_error("Expected 'file' keyword for mesh");
            }
            
            stream >> file_value;
            // Remove quotes
            file_value = file_value.substr(1, file_value.size() - 2);
            
            // Create and store the mesh
            auto mesh = std::make_shared<DwnMesh>(file_value);
            m_mesh_manager.add(tag_value, mesh);
            
            // Skip to "end"
            while (stream >> token && token != "end") {}
        } else if (token == "shader") {
            std::string tag_keyword, tag_value;
            std::string vertex_keyword, vertex_value;
            std::string fragment_keyword, fragment_value;
            
            stream >> tag_keyword;
            if (tag_keyword != "tag") {
                throw std::runtime_error("Expected 'tag' keyword for shader");
            }
            
            stream >> tag_value;
            // Remove quotes
            tag_value = tag_value.substr(1, tag_value.size() - 2);
            
            stream >> vertex_keyword;
            if (vertex_keyword != "vertex") {
                throw std::runtime_error("Expected 'vertex' keyword for shader");
            }
            
            stream >> vertex_value;
            // Remove quotes
            vertex_value = vertex_value.substr(1, vertex_value.size() - 2);
            
            stream >> fragment_keyword;
            if (fragment_keyword != "fragment") {
                throw std::runtime_error("Expected 'fragment' keyword for shader");
            }
            
            stream >> fragment_value;
            // Remove quotes
            fragment_value = fragment_value.substr(1, fragment_value.size() - 2);
            
            // Create and store the shader
            auto shader = std::make_shared<DwnShader>(vertex_value, fragment_value);
            m_shader_manager.add(tag_value, shader);
            
            // Skip to "end"
            while (stream >> token && token != "end") {}
        }
    }
}

void DwnScene::parse_objects_section(std::istringstream& stream)
{
    // Create root object
    std::shared_ptr<DwnObject> root_obj = parse_object(stream);
    if (!root_obj) {
        throw std::runtime_error("Failed to parse root object");
    }
    // Instead of just copying the tag, use the entire parsed object
    m_root = std::move(root_obj);
}

std::shared_ptr<DwnObject> DwnScene::parse_object(std::istringstream& stream)
{
    std::string token;
    std::string tag_value;
    std::string mesh_tag;
    std::string shader_tag;
    
    // Get the tag for this object
    stream >> token;
    if (token != "tag") {
        throw std::runtime_error("Expected 'tag' keyword for object");
    }
    
    stream >> tag_value;
    // Remove quotes
    tag_value = tag_value.substr(1, tag_value.size() - 2);
    
    auto object = std::make_shared<DwnObject>(tag_value);
    
    // Parse object properties
    while (stream >> token) {
        if (token == "end") {
            break;
        } else if (token == "mesh") {
            stream >> mesh_tag;
            // Remove quotes
            mesh_tag = mesh_tag.substr(1, mesh_tag.size() - 2);
            
            m_mesh_manager.get(mesh_tag);
            
            object->set_mesh(m_mesh_manager.get(mesh_tag));
            
            // Set the mesh for the object (you may need to add this method to DwnObject)
            // object->set_mesh(m_meshes[mesh_tag]);
        } else if (token == "shader") {
            stream >> shader_tag;
            // Remove quotes
            shader_tag = shader_tag.substr(1, shader_tag.size() - 2);
            
            m_shader_manager.get(shader_tag);
            
            // Set the shader for the object (you may need to add this method to DwnObject)
            object->set_shader(m_shader_manager.get(shader_tag));
        } else if (token == "transform") {
            parse_transform(stream, *object);
        } else if (token == "objects") {
            // Parse child object
            auto child = parse_object(stream);
            object->add_child(child);
        }
    }
    
    return object;
}

void DwnScene::parse_transform(std::istringstream& stream, DwnComponent& component)
{
    std::string token;
    glm::vec3 position(0.0f);
    glm::vec3 rotation(0.0f);
    glm::vec3 scale(1.0f);
    
    while (stream >> token) {
        if (token == "end") {
            break;
        } else if (token == "position") {
            stream >> position.x >> position.y >> position.z;
        } else if (token == "rotation") {
            stream >> rotation.x >> rotation.y >> rotation.z;
        } else if (token == "scale") {
            stream >> scale.x >> scale.y >> scale.z;
        }
    }
    
    // Apply the transformation to the component
    component.transform().set_position(position);
    component.transform().set_rotation(rotation);
    component.transform().set_scale(scale);

    // component.rotate(rotation);
    // component.scale(scale);
}


