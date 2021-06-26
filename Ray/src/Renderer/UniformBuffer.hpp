#pragma once

#include "Core/Core.hpp"
#include "Renderer/Buffer.hpp"

namespace Ray
{
    struct UniformBufferLayoutElement
    {
        std::string name;
        ShaderDatatype type;
        uint32_t values = 1;

        uint32_t offset = uint32_t(-1);
    };

    using UniformBufferLayout = std::vector<UniformBufferLayoutElement>;

    class UniformBuffer
    {
    public:
        UniformBuffer() = default;
        virtual ~UniformBuffer() = default;

        virtual const UniformBufferLayout &GetLayout() const = 0;

        virtual void SetData(void *) = 0;
        //Set Uniform by Index in Uniform Buffer Layout
        virtual void UpdateUniform(uint32_t, void *) = 0;
        //Set Uniform by Name in Uniform Buffer Layout
        virtual void UpdateUniform(const std::string &, void *) = 0;

        virtual intptr_t GetRendererID() const = 0;

    public:
        static Ref<UniformBuffer> Create(const UniformBufferLayout &, uint32_t);
    };
}