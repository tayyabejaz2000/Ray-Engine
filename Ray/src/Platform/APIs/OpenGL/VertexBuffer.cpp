#include <glad/glad.h>

#include "Platform/APIs/OpenGL/VertexBuffer.hpp"

namespace Ray::OpenGL
{
    uint32_t ShaderDatatypeLookup::s_TypeLookup[] = {
        [(uint32_t)ShaderDatatype::Int] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Bool] = GL_BOOL,
        [(uint32_t)ShaderDatatype::Half] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Int2] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint2] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Bool2] = GL_BOOL,
        [(uint32_t)ShaderDatatype::Half2] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float2] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double2] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Int3] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint3] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Bool3] = GL_BOOL,
        [(uint32_t)ShaderDatatype::Half3] = GL_HALF_FLOAT,
        [(uint32_t)ShaderDatatype::Float3] = GL_FLOAT,
        [(uint32_t)ShaderDatatype::Double3] = GL_DOUBLE,

        [(uint32_t)ShaderDatatype::Int4] = GL_INT,
        [(uint32_t)ShaderDatatype::Uint4] = GL_UNSIGNED_INT,
        [(uint32_t)ShaderDatatype::Bool4] = GL_BOOL,
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
    uint8_t ShaderDatatypeLookup::s_CountLookup[] = {
        [(uint32_t)ShaderDatatype::Int] = 1,
        [(uint32_t)ShaderDatatype::Uint] = 1,
        [(uint32_t)ShaderDatatype::Bool] = 1,
        [(uint32_t)ShaderDatatype::Half] = 1,
        [(uint32_t)ShaderDatatype::Float] = 1,
        [(uint32_t)ShaderDatatype::Double] = 1,

        [(uint32_t)ShaderDatatype::Int2] = 2,
        [(uint32_t)ShaderDatatype::Uint2] = 2,
        [(uint32_t)ShaderDatatype::Bool2] = 2,
        [(uint32_t)ShaderDatatype::Half2] = 2,
        [(uint32_t)ShaderDatatype::Float2] = 2,
        [(uint32_t)ShaderDatatype::Double2] = 2,

        [(uint32_t)ShaderDatatype::Int3] = 3,
        [(uint32_t)ShaderDatatype::Uint3] = 3,
        [(uint32_t)ShaderDatatype::Bool3] = 3,
        [(uint32_t)ShaderDatatype::Half3] = 3,
        [(uint32_t)ShaderDatatype::Float3] = 3,
        [(uint32_t)ShaderDatatype::Double3] = 3,

        [(uint32_t)ShaderDatatype::Int4] = 4,
        [(uint32_t)ShaderDatatype::Uint4] = 4,
        [(uint32_t)ShaderDatatype::Bool4] = 4,
        [(uint32_t)ShaderDatatype::Half4] = 4,
        [(uint32_t)ShaderDatatype::Float4] = 4,
        [(uint32_t)ShaderDatatype::Double4] = 4,

        [(uint32_t)ShaderDatatype::Mat2] = 2,
        [(uint32_t)ShaderDatatype::Mat2x3] = 2,
        [(uint32_t)ShaderDatatype::Mat2x4] = 2,

        [(uint32_t)ShaderDatatype::Mat3x2] = 3,
        [(uint32_t)ShaderDatatype::Mat3] = 3,
        [(uint32_t)ShaderDatatype::Mat3x4] = 3,

        [(uint32_t)ShaderDatatype::Mat4x2] = 4,
        [(uint32_t)ShaderDatatype::Mat4x3] = 4,
        [(uint32_t)ShaderDatatype::Mat4] = 4,
    };
    uint16_t ShaderDatatypeLookup::s_SizeLookup[] = {
        [(uint32_t)ShaderDatatype::Int] = sizeof(GLint),
        [(uint32_t)ShaderDatatype::Uint] = sizeof(GLuint),
        [(uint32_t)ShaderDatatype::Bool] = sizeof(GLboolean),
        [(uint32_t)ShaderDatatype::Half] = sizeof(GLhalf),
        [(uint32_t)ShaderDatatype::Float] = sizeof(GLfloat),
        [(uint32_t)ShaderDatatype::Double] = sizeof(GLdouble),

        [(uint32_t)ShaderDatatype::Int2] = sizeof(GLint) * 2,
        [(uint32_t)ShaderDatatype::Uint2] = sizeof(GLuint) * 2,
        [(uint32_t)ShaderDatatype::Bool2] = sizeof(GLboolean) * 2,
        [(uint32_t)ShaderDatatype::Half2] = sizeof(GLhalf) * 2,
        [(uint32_t)ShaderDatatype::Float2] = sizeof(GLfloat) * 2,
        [(uint32_t)ShaderDatatype::Double2] = sizeof(GLdouble) * 2,

        [(uint32_t)ShaderDatatype::Int3] = sizeof(GLint) * 3,
        [(uint32_t)ShaderDatatype::Uint3] = sizeof(GLuint) * 3,
        [(uint32_t)ShaderDatatype::Bool3] = sizeof(GLboolean) * 3,
        [(uint32_t)ShaderDatatype::Half3] = sizeof(GLhalf) * 3,
        [(uint32_t)ShaderDatatype::Float3] = sizeof(GLfloat) * 3,
        [(uint32_t)ShaderDatatype::Double3] = sizeof(GLdouble) * 3,

        [(uint32_t)ShaderDatatype::Int4] = sizeof(GLint) * 4,
        [(uint32_t)ShaderDatatype::Uint4] = sizeof(GLuint) * 4,
        [(uint32_t)ShaderDatatype::Bool4] = sizeof(GLboolean) * 4,
        [(uint32_t)ShaderDatatype::Half4] = sizeof(GLhalf) * 4,
        [(uint32_t)ShaderDatatype::Float4] = sizeof(GLfloat) * 4,
        [(uint32_t)ShaderDatatype::Double4] = sizeof(GLdouble) * 4,

        [(uint32_t)ShaderDatatype::Mat2] = sizeof(GLfloat) * 4,
        [(uint32_t)ShaderDatatype::Mat2x3] = sizeof(GLfloat) * 6,
        [(uint32_t)ShaderDatatype::Mat2x4] = sizeof(GLfloat) * 8,

        [(uint32_t)ShaderDatatype::Mat3x2] = sizeof(GLfloat) * 6,
        [(uint32_t)ShaderDatatype::Mat3] = sizeof(GLfloat) * 9,
        [(uint32_t)ShaderDatatype::Mat3x4] = sizeof(GLfloat) * 12,

        [(uint32_t)ShaderDatatype::Mat4x2] = sizeof(GLfloat) * 8,
        [(uint32_t)ShaderDatatype::Mat4x3] = sizeof(GLfloat) * 12,
        [(uint32_t)ShaderDatatype::Mat4] = sizeof(GLfloat) * 16,
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

    uint32_t GetStride(const VertexBufferLayout &layout)
    {
        auto stride = 0u;
        for (auto &elem : layout)
            stride += ShaderDatatypeLookup::GetSize(elem.type);
        return stride;
    }
}