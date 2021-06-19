#include <glad/glad.h>

#include "Platform/APIs/OpenGL/VertexArray.hpp"
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

    void VertexArray::AddVertexBuffer(const Ref<Ray::VertexBuffer> &buffer)
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
                                       ShaderDatatypeLookup::GetComponentCount(layoutElem.type),
                                       ShaderDatatypeLookup::GetType(layoutElem.type),
                                       stride,
                                       reinterpret_cast<const void *>(offset));
                offset += ShaderDatatypeLookup::GetSize(layoutElem.type);
                break;
            case ShaderDatatype::Mat2:
            case ShaderDatatype::Mat2x3:
            case ShaderDatatype::Mat2x4:
            case ShaderDatatype::Mat3x2:
            case ShaderDatatype::Mat3:
            case ShaderDatatype::Mat3x4:
            case ShaderDatatype::Mat4x2:
            case ShaderDatatype::Mat4x3:
            case ShaderDatatype::Mat4:
                ///TODO: Implement Matrix Vertex Attribute after a bit research
                ///Ignored for now
                --m_vertexBufferIndex;
                break;
            default:
                glVertexAttribPointer(m_vertexBufferIndex,
                                      ShaderDatatypeLookup::GetComponentCount(layoutElem.type),
                                      ShaderDatatypeLookup::GetType(layoutElem.type),
                                      layoutElem.normalized ? GL_TRUE : GL_FALSE,
                                      stride,
                                      reinterpret_cast<const void *>(offset));
                offset += ShaderDatatypeLookup::GetSize(layoutElem.type);
                break;
            }
            ++m_vertexBufferIndex;
        }
        m_vertexBuffers.push_back(buffer);
    }

    void VertexArray::SetIndexBuffer(const Ref<Ray::IndexBuffer> &buffer)
    {
        glBindVertexArray(m_rendererID);
        buffer->Bind();

        m_indexBuffer = buffer;
    }
}