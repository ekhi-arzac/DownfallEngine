#include "engine/managers/dwn_manager.hpp"
#include "dwn_manager.hpp"

template <typename T>
inline T &DwnManager<T>::get(const std::string &tag)
{
    auto it = m_resources.find(tag);
    if (it != m_resources.end()) {
        return *(it->second);
    } else {
        throw std::runtime_error("Resource not found: " + tag);
    }
}

template <typename T>
void DwnManager<T>::add(const std::string &tag, std::shared_ptr<T> resource)
{
}

template<typename T>
void DwnManager<T>::release(const std::string & tag)
{
    auto it = m_resources.find(tag);
    if (it != m_resources.end()) {
        m_resources.erase(it);
    } else {
        throw std::runtime_error("Resource not found: " + tag);
    }
}