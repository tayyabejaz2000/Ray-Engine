#pragma once

#include "Core/Core.hpp"
#include "Core/RayObject.hpp"

namespace Ray
{
    ///TODO: Move to Graphics API Specific Implementation
    enum class ShaderDatatype : uint8_t
    {
        //Single Values

        Int,    //32-bit Integer
        Uint,   //32-bit Unsigned Integer
        Bool,   //8-bit boolean with 2 possible values (true/false)
        Half,   //16-bit half precision floating value
        Float,  //32-bit standard floating value
        Double, //64-bit high precision floating value

        //Vec2 Values

        Int2,    //32-bit Integer (vec2)
        Uint2,   //32-bit Unsigned Integer (vec2)
        Bool2,   //8-bit boolean with 2 possible values (true/false) (vec2)
        Half2,   //16-bit half precision floating value (vec2)
        Float2,  //32-bit standard floating value (vec2)
        Double2, //64-bit high precision floating value (vec2)

        //Vec3 Values

        Int3,    //32-bit Integer (vec3)
        Uint3,   //32-bit Unsigned Integer (vec3)
        Bool3,   //8-bit boolean with 2 possible values (true/false) (vec3)
        Half3,   //16-bit half precision floating value (vec3)
        Float3,  //32-bit standard floating value (vec3)
        Double3, //64-bit high precision floating value (vec3)

        //Vec4 Values

        Int4,    //32-bit Integer (vec4)
        Uint4,   //32-bit Unsigned Integer (vec4)
        Bool4,   //8-bit boolean with 2 possible values (true/false) (vec4)
        Half4,   //16-bit half precision floating value (vec4)
        Float4,  //32-bit standard floating value (vec4)
        Double4, //64-bit high precision floating value (vec4)

        //Matrices

        Mat2,   //2x2 Matrix floating values
        Mat2x3, //2x3 Matrix floating values
        Mat2x4, //2x4 Matrix floating values

        Mat3x2, //3x2 Matrix floating values
        Mat3,   //3x3 Matrix floating values
        Mat3x4, //3x4 Matrix floating values

        Mat4x2, //4x2 Matrix floating values
        Mat4x3, //4x3 Matrix floating values
        Mat4,   //4x4 Matrix floating values
    };

    struct VertexBufferLayoutElement
    {
        std::string name;
        ShaderDatatype type;
        bool normalized = false;
    };

    using VertexBufferLayout = std::vector<VertexBufferLayoutElement>;

    class VertexBuffer : public RayObject
    {
    public:
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const VertexBufferLayout &layout) = 0;
        virtual const VertexBufferLayout &GetLayout() const = 0;

        virtual void SetData(void *, std::size_t) = 0;
        virtual void GetData(void *, std::size_t) const = 0;

    public:
        static Ref<VertexBuffer> Create();
    };

    class IndexBuffer : public RayObject
    {
    public:
        IndexBuffer() = default;
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetIndices(void *, std::size_t) = 0;
        virtual void GetIndices(void *, std::size_t) const = 0;

    public:
        static Ref<IndexBuffer> Create();
    };
}