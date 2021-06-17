#include <glad/glad.h>

#include "VertexArray.hpp"
#include "Platform/APIs/OpenGL/VertexBuffer.hpp"

namespace Ray::OpenGL
{
    VertexArray::VertexArray() : m_vertexBufferIndex(0u)
    {
        glCreateVertexArrays(1, &m_rendererID);
    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_rendererID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const Ref<VertexBuffer> &buffer)
    {
        const auto &layout = buffer->GetLayout();

        auto stride = GetStride(layout);
        auto offset = 0u;

        glBindVertexArray(m_rendererID);
        buffer->Bind();

        for (auto &layoutElem : layout)
        {
            glEnableVertexAttribArray(m_vertexBufferIndex);
            switch (layoutElem.type)
            {
            case ShaderDatatype::Int:
            case ShaderDatatype::Int2:
            case ShaderDatatype::Int3:
            case ShaderDatatype::Int4:
            case ShaderDatatype::Uint:
            case ShaderDatatype::Uint2:
            case ShaderDatatype::Uint3:
            case ShaderDatatype::Uint4:
            case ShaderDatatype::Bool:
            case ShaderDatatype::Bool2:
            case ShaderDatatype::Bool3:
            case ShaderDatatype::Bool4:
                glVertexAttribIPointer(m_vertexBufferIndex,
                                       ShaderDatatypeResolver::GetSize(layoutElem.type),
                                       ShaderDatatypeResolver::GetType(layoutElem.type),
                                       stride,
                                       reinterpret_cast<const void *>(offset));
                break;
            default:
                glVertexAttribPointer(m_vertexBufferIndex,
                                      ShaderDatatypeResolver::GetSize(layoutElem.type),
                                      ShaderDatatypeResolver::GetType(layoutElem.type),
                                      layoutElem.normalized ? GL_TRUE : GL_FALSE,
                                      stride,
                                      reinterpret_cast<const void *>(offset));
                break;
            }
            ++m_vertexBufferIndex;
        }
        m_vertexBuffers.push_back(buffer);
    }

    void VertexArray::SetIndexBuffer(const Ref<IndexBuffer> &buffer)
    {
        glBindVertexArray(m_rendererID);
        buffer->Bind();

        m_indexBuffer = buffer;
    }
}