#pragma once

#include "Core/Core.hpp"
#include "Renderer/Shader.hpp"

namespace Ray::OpenGL
{
    class Shader : public Ray::Shader
    {
    public:
        Shader(const std::string &, const std::string &);
        virtual ~Shader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual intptr_t GetRendererID() const override { return m_rendererID; }

    private:
        uid_t m_rendererID;
    };
}