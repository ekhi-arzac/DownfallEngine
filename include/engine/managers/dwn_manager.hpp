#pragma once

#include <unordered_map>
#include <memory>

template <typename T>
class DwnManager {
public:
    static DwnManager& instance();

    T& get(const std::string& tag);
    void add(const std::string& tag, std::shared_ptr<T> resource);
    void release(const std::string& tag);
    
private:
    DwnManager() = default;
    ~DwnManager() = default;
    DwnManager(const DwnManager&) = delete;
    DwnManager& operator=(const DwnManager&) = delete;
    DwnManager(DwnManager&&) = delete;
    DwnManager& operator=(DwnManager&&) = delete;

    std::unordered_map<std::string, std::shared_ptr<T>> m_resources;
};
