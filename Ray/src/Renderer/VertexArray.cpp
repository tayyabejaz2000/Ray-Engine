#include "VertexArray.hpp"

#include "Platform/APIs/OpenGL/VertexArray.hpp"

namespace Ray
{
    Ref<VertexArray> VertexArray::Create()
    {
        return CreateRef<OpenGL::VertexArray>();
    }
}