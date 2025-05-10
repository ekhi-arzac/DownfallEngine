#pragma once
#include <string>


class DwnResource {
    public:
        DwnResource(const std::string& file_path, const std::string& tag);
        virtual ~DwnResource();

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void load() = 0;
        virtual void release() = 0;

        const std::string& get_tag() const { return m_tag; }
        const std::string& get_file_path() const { return m_file_path; }
    private:
        const std::string m_file_path;
        const std::string m_tag;
};