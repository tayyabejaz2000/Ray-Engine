#include <glad/glad.h>

#include "VertexBuffer.hpp"

namespace Ray::OpenGL
{
    uint32_t ShaderDatatypeResolver::s_TypeLookup[] = {
        [(uint32_t)ShaderDatatype::Int] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Half] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Int2] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint2] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Half2] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float2] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double2] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Int3] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint3] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Half3] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float3] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double3] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Int4] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint4] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Half4] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float4] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double4] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Mat2] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Mat2x3] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Mat2x4] = GL_FLOAT,

        [(uint32_t)ShaderDatatype::Mat3x2] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Mat3] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Mat3x4] = GL_FLOAT,

        [(uint32_t)ShaderDatatype::Mat4x2] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Mat4x3] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Mat4] = GL_FLOAT,
    };
    uint8_t ShaderDatatypeResolver::s_SizeLookup[] = {
        [(uint32_t)ShaderDatatype::Int] = 1,
        [(uint32_t)ShaderDatatype::Uint] = 1,
        [(uint32_t)ShaderDatatype::Half] = 1,
        [(uint32_t)ShaderDatatype::Float] = 1,
        [(uint32_t)ShaderDatatype::Double] = 1,

        [(uint32_t)ShaderDatatype::Int2] = 2,
        [(uint32_t)ShaderDatatype::Uint2] = 2,
        [(uint32_t)ShaderDatatype::Half2] = 2,
        [(uint32_t)ShaderDatatype::Float2] = 2,
        [(uint32_t)ShaderDatatype::Double2] = 2,

        [(uint32_t)ShaderDatatype::Int3] = 3,
        [(uint32_t)ShaderDatatype::Uint3] = 3,
        [(uint32_t)ShaderDatatype::Half3] = 3,
        [(uint32_t)ShaderDatatype::Float3] = 3,
        [(uint32_t)ShaderDatatype::Double3] = 3,

        [(uint32_t)ShaderDatatype::Int4] = 4,
        [(uint32_t)ShaderDatatype::Uint4] = 4,
        [(uint32_t)ShaderDatatype::Half4] = 4,
        [(uint32_t)ShaderDatatype::Float4] = 4,
        [(uint32_t)ShaderDatatype::Double4] = 4,

        [(uint32_t)ShaderDatatype::Mat2] = 4,
        [(uint32_t)ShaderDatatype::Mat2x3] = 6,
        [(uint32_t)ShaderDatatype::Mat2x4] = 8,

        [(uint32_t)ShaderDatatype::Mat3x2] = 6,
        [(uint32_t)ShaderDatatype::Mat3] = 9,
        [(uint32_t)ShaderDatatype::Mat3x4] = 12,

        [(uint32_t)ShaderDatatype::Mat4x2] = 8,
        [(uint32_t)ShaderDatatype::Mat4x3] = 12,
        [(uint32_t)ShaderDatatype::Mat4] = 16,
    };

    VertexBuffer::VertexBuffer(std::size_t bufferSize) : Ray::VertexBuffer()
    {
        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
    }
    VertexBuffer::VertexBuffer(void *data, std::size_t bufferSize) : Ray::VertexBuffer()
    {
        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
    }
    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_rendererID);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(void *data, std::size_t dataSize)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, data);
    }
    //Think about it (Would you ever need it)
    void VertexBuffer::GetData(void *data, std::size_t bufferSize) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, data);
    }
}