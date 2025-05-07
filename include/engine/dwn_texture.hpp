#pragma once
#include <string>
#include <memory>
#include <glad/glad.h>

class DwnTexture {
public:
    DwnTexture(const std::string& file_path, const std::string& tag);
    ~DwnTexture();

    void bind() const;
    void unbind() const;

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
    int get_channels() const { return m_channels; }
    uint32_t get_texture_id() const { return m_texture_id; }

    const std::string& get_tag() const { return tag; }
private:
    uint32_t m_texture_id;
    int m_width;
    int m_height;
    int m_channels;
    std::string tag;
};