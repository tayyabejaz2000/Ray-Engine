#include <glad/glad.h>

#include "Platform/APIs/OpenGL/Shader.hpp"

namespace Ray::OpenGL
{
    Shader::Shader(const std::string &VSSource, const std::string &FSSource) : m_rendererID(glCreateProgram())
    {
        int32_t success = 0;

        //Compile and Attach Vertex Shader
        {
            const auto vsSource = VSSource.data();
            uint32_t vsShaderRendererID = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vsShaderRendererID, 1, &vsSource, nullptr);
            glCompileShader(vsShaderRendererID);
            glGetShaderiv(vsShaderRendererID, GL_COMPILE_STATUS, &success);
            if (!success)
                throw std::runtime_error("Failed to compile Vertex Shader");
            glAttachShader(m_rendererID, vsShaderRendererID);
            glDeleteShader(vsShaderRendererID);
        }
        //Compile and Attach Fragment/Pixel Shader
        {
            const auto fsSource = VSSource.data();
            uint32_t fsShaderRendererID = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fsShaderRendererID, 1, &fsSource, nullptr);
            glCompileShader(fsShaderRendererID);
            glGetShaderiv(fsShaderRendererID, GL_COMPILE_STATUS, &success);
            if (!success)
                throw std::runtime_error("Failed to compile Fragment/Pixel Shader");
            glAttachShader(m_rendererID, fsShaderRendererID);
            glDeleteShader(fsShaderRendererID);
        }

        glLinkProgram(m_rendererID);
        glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);
        if (!success)
            throw std::runtime_error("Failed to Link Shader");
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_rendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_rendererID);
    }
    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
}