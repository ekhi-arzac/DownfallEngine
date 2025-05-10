#pragma once

#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "engine/resources/dwn_resource.hpp"

template <typename T = DwnResource>
class DwnResourceManager {
public:
    static DwnResourceManager& instance() {
        static DwnResourceManager<T> instance;
        return instance;
    }

    std::shared_ptr<T> get(const std::string& tag) {
        auto it = m_resources.find(tag);
        if (it != m_resources.end()) {
            return *(it->second);
        } else {
            throw std::runtime_error("Resource not found: " + tag);
        }
    }
    
    void add(const std::string& tag, std::shared_ptr<T> resource) {
        auto it = m_resources.find(tag);
        if (it == m_resources.end()) {
            m_resources[tag] = resource;
        } else {
            throw std::runtime_error("Resource already exists: " + tag);
        }
    }
    
    void release(const std::string& tag) {
        auto it = m_resources.find(tag);
        if (it != m_resources.end()) {
            m_resources.erase(it);
        } else {
            throw std::runtime_error("Resource not found: " + tag);
        }
    }
    
private:
    DwnResourceManager() = default;
    ~DwnResourceManager() = default;
    DwnResourceManager(const DwnResourceManager&) = delete;
    DwnResourceManager& operator=(const DwnResourceManager&) = delete;
    DwnResourceManager(DwnResourceManager&&) = delete;
    DwnResourceManager& operator=(DwnResourceManager&&) = delete;

    std::unordered_map<std::string, std::shared_ptr<T>> m_resources;
};
