#include "Renderer/Buffer.hpp"

#include "Platform/APIs/OpenGL/VertexBuffer.hpp"
#include "Platform/APIs/OpenGL/IndexBuffer.hpp"

namespace Ray
{
    Ref<VertexBuffer> VertexBuffer::Create(std::size_t bufferSize)
    {
        return CreateRef<OpenGL::VertexBuffer>(bufferSize);
    }
    Ref<VertexBuffer> VertexBuffer::Create(void *data, std::size_t bufferSize)
    {
        return CreateRef<OpenGL::VertexBuffer>(data, bufferSize);
    }
    Ref<IndexBuffer> IndexBuffer::Create(void *data, std::size_t bufferSize)
    {
        return CreateRef<OpenGL::IndexBuffer>(data, bufferSize);
    }
}
