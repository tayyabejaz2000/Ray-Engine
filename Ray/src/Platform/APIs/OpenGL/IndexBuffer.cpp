#include <glad/glad.h>

#include "Platform/APIs/OpenGL/IndexBuffer.hpp"

namespace Ray::OpenGL
{
    IndexBuffer::IndexBuffer(void *indices, std::size_t count)
    {
        glCreateBuffers(1, &m_rendererID);
        SetIndices(indices, count);
    }
    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_rendererID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }
    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::SetIndices(void *indices, std::size_t count)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    void IndexBuffer::GetIndices(void *indices, std::size_t bufferSize) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, indices);
    }
}