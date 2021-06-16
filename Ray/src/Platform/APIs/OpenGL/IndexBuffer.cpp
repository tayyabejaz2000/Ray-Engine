#include <glad/glad.h>

#include "IndexBuffer.hpp"

namespace Ray::OpenGL
{
    IndexBuffer::IndexBuffer(void *indices, std::size_t bufferSize)
    {
        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(uint32_t), indices, GL_STATIC_DRAW);
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

    void IndexBuffer::SetIndices(void *indices, std::size_t bufferSize)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    void IndexBuffer::GetIndices(void *indices, std::size_t bufferSize) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, indices);
    }
}