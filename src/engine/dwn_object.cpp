#include "engine/dwn_object.hpp"
#include <glad/glad.h>
#include "dwn_object.hpp"

void DwnObject::bind()
{
    if (m_mesh) {
        m_mesh->bind();
    }
    if (m_shader) {
        
        m_shader->bind();

    }
    if (m_texture) {
        m_texture->bind();
    }
    



}