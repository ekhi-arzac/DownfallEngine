#include "engine/dwn_shader.hpp"

#include <glad/glad.h>

#include <stdexcept>

#include <fstream>
#include <sstream>
#include <iostream>

void log_output(GLuint shader, const std::string& type) {
    int success;
    char info_log[512];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, info_log);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

DwnShader::DwnShader(const std::string& tag, const std::string &vertex_path, const std::string &fragment_path) : m_tag(tag)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream v_shader_file(vertex_path
        , std::ios::in);
    std::ifstream f_shader_file(fragment_path 
        , std::ios::in);
    if (!v_shader_file.is_open()) {
        throw std::runtime_error("Failed to open vertex shader file: " + vertex_path);
    }
    if (!f_shader_file.is_open()) {
        throw std::runtime_error("Failed to open fragment shader file: " + fragment_path);
    }

    std::stringstream v_shader_stream;
    std::stringstream f_shader_stream;

    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();

    v_shader_file.close();
    f_shader_file.close();

    vertex_code = v_shader_stream.str();
    fragment_code = f_shader_stream.str();
    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();

    // 2. Compile shaders
    GLuint vertex, fragment;
    
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, NULL);
    glCompileShader(vertex);
    log_output(vertex, "VERTEX");
    
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, NULL);
    glCompileShader(fragment);
    log_output(fragment, "FRAGMENT");
    
    // Shader Program
    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex);
    glAttachShader(m_program_id, fragment);
    glLinkProgram(m_program_id);

    log_output(m_program_id, "PROGRAM");
    
    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
DwnShader::~DwnShader()
{
    glDeleteProgram(m_program_id);
}

