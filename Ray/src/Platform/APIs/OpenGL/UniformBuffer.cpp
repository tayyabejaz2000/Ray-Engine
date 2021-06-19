#include <glad/glad.h>

#include "Platform/APIs/OpenGL/VertexBuffer.hpp"
#include "Platform/APIs/OpenGL/UniformBuffer.hpp"

namespace Ray::OpenGL
{
    UniformBuffer::UniformBuffer(const UniformBufferLayout &layout, uint32_t binding) : m_layout(layout)
    {
        ///TODO: Create UniformBufferLayout own class and move this computation there
        auto offset = 0u;
        for (auto &layoutElem : m_layout)
        {
            layoutElem.offset = offset;
            offset += ShaderDatatypeLookup::GetSize(layoutElem.type);
        }
        m_layoutSize = offset;

        glCreateBuffers(1, &m_rendererID);
        glNamedBufferData(m_rendererID, m_layoutSize, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_rendererID);
    }
    UniformBuffer::~UniformBuffer()
    {
        glDeleteBuffers(1, &m_rendererID);
    }
    void UniformBuffer::SetData(void *data)
    {
        glNamedBufferSubData(m_rendererID, 0, m_layoutSize, data);
    }
    void UniformBuffer::UpdateUniform(uint32_t index, void *data)
    {
        const auto &layoutElem = m_layout[index];
        glNamedBufferSubData(m_rendererID, layoutElem.offset, ShaderDatatypeLookup::GetSize(layoutElem.type) * layoutElem.values, data);
    }
    void UniformBuffer::UpdateUniform(const std::string &name, void *data)
    {
        UniformBufferLayoutElement *elem = nullptr;
        for (auto &layoutElem : m_layout)
            if (layoutElem.name == name)
                elem = &layoutElem;
        if (elem)
            glNamedBufferSubData(m_rendererID, elem->offset, ShaderDatatypeLookup::GetSize(elem->type) * elem->values, data);
    }
}