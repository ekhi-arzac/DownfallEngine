#include "engine/resources/dwn_resource.hpp"

DwnResource::DwnResource(const std::string& file_path, const std::string& tag)
    : m_file_path(file_path), m_tag(tag) {
        this->load();
}

DwnResource::~DwnResource() {
    this->release();
}