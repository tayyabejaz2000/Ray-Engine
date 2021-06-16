#pragma once

#include "Core/Core.hpp"
#include "Renderer/Buffer.hpp"

namespace Ray
{
    namespace OpenGL
    {
        class IndexBuffer : public Ray::IndexBuffer
        {
        public:
            IndexBuffer(void *, std::size_t);
            virtual ~IndexBuffer();

        public:
            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void GetIndices(void *, std::size_t) const override;
            virtual void SetIndices(void *, std::size_t) override;

        private:
            uid_t m_rendererID;
        };
    }
}