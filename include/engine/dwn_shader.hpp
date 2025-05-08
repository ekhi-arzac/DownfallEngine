#pragma once
#include <stdint.h>
#include <string>

/**
 * @brief A class that represents a shader program.
 *  
 */
class DwnShader {
public:
    DwnShader(const std::string& tag, const std::string& vertex_path, const std::string& fragment_path);
    ~DwnShader();

    void use() const;

private:
    uint32_t m_program_id;
    const std::string m_tag;
};