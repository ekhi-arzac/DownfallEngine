#pragma once

#include <string>
#include <vector>
#include <stdint.h>

class DwnMesh {
public:
    /**
     * @brief Construct a new Mesh object
     * 
     * @param tag object tag
     * @param path path to the .obj file
     * @details The path should be relative to the current working directory.
     */
    DwnMesh(const std::string& tag, const std::string& path);

    void bind() const;
    void draw() const;
    void unbind() const;
private:
    
    uint32_t VAO, VBO, EBO;
    uint32_t m_index_count;
    const std::string m_tag;
};