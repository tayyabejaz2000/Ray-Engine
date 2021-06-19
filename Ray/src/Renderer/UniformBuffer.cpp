#include "UniformBuffer.hpp"

#include "Platform/APIs/OpenGL/UniformBuffer.hpp"

namespace Ray
{
    Ref<UniformBuffer> UniformBuffer::Create(const UniformBufferLayout &layout, uint32_t binding)
    {
        return CreateRef<Ray::OpenGL::UniformBuffer>(layout, binding);
    }
}