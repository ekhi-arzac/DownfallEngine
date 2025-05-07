#include "engine/dwn_texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "engine/stb_image.h"

#include <stdexcept>

DwnTexture::DwnTexture(const std::string &file_path, const std::string &tag, const DwnTextureType &type) : m_type(type)
{
    this->tag = tag;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file_path.c_str(), &m_width, &m_height, &m_channels, 0);
    if (data) {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
    } else {
        std::runtime_error("Failed to load texture: " + file_path);
    }
    stbi_image_free(data);
}
   