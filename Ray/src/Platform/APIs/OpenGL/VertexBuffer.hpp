#include "Renderer/Buffer.hpp"

namespace Ray::OpenGL
{
    uint32_t GetStride(const VertexBufferLayout &layout)
    {
        if (layout.size() == 0)
            return 0;
        auto stride = 0u;
        for (auto &elem : layout)
        {
            ///TODO: Get Size of VertexBufferLayoutElement::type from Graphics Specific API
            ///TODO: Add that size to stride
        }
        return stride;
    }

    //Returns the offset of a specific VertexBufferLayoutElement based on its index
    uint32_t GetOffset(const VertexBufferLayout &layout, int index)
    {
        if (index <= 0 || layout.size() <= index)
            return 0;
        auto i = 0;
        auto offset = 0u;
        for (auto &elem : layout)
        {
            if (i == index)
                break;
            ///TODO: Add size of elem to offset
            ++i;
        }
        return offset;
    }

    class ShaderDatatypeResolver
    {
    private:
        static uint32_t s_TypeLookup[];
        static uint8_t s_SizeLookup[];

    public:
        static inline uint32_t GetType(ShaderDatatype type)
        {
            return s_TypeLookup[(uint32_t)type];
        }
        static inline uint32_t GetSize(ShaderDatatype type)
        {
            return s_SizeLookup[(uint32_t)type];
        }
    };

    class VertexBuffer : public Ray::VertexBuffer
    {
    public:
        VertexBuffer(std::size_t);
        VertexBuffer(void *, std::size_t);
        virtual ~VertexBuffer();

    public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetLayout(const VertexBufferLayout &layout) override { m_layout = layout; }
        virtual const VertexBufferLayout &GetLayout() const override { return m_layout; }

        virtual void GetData(void *, std::size_t) const override;
        virtual void SetData(void *, std::size_t) override;

    private:
        uid_t m_rendererID;
        VertexBufferLayout m_layout;
    };
}