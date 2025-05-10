#pragma once
#include <stdint.h>
#include <string>
#include "engine/resources/dwn_resource.hpp"
#include <glm/mat4x4.hpp>

/**
 * @brief A class that represents a shader program.
 *  
 */
class DwnShader : public DwnResource {
public:
    DwnShader(const std::string& tag, const std::string& vertex_path, const std::string& fragment_path);
    ~DwnShader();

    void bind() const override;
    void unbind() const override;

    void load() override;
    void release() override;

    uint32_t get_program_id() const { return m_program_id; }

    void set_uniform(const std::string& name, const glm::mat4& value);
    void set_uniform(const std::string& name, const glm::vec3& value);
    void set_uniform(const std::string& name, const glm::vec4& value);
    void set_uniform(const std::string& name, float value);
    void set_uniform(const std::string& name, int value);
    


private:
    uint32_t m_program_id;
    std::string m_vertex_path;
    std::string m_fragment_path;
};