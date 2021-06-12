#pragma once

#include "raypch.hpp"
#include "Platform/Util/PlatformDetection.hpp"
//Linux Defines
#if defined(RAY_PLATFORM_LINUX)

#if defined(RAY_BUILD_SHARED)
#define RAYAPI __attribute__((visibility("default")))
#elif defined(RAY_BUILD_STATIC)
#define RAYAPI
#else
#define RAYAPI
#endif

#else

#define RAYAPI

#endif

#define BIT(x) 1 << x

namespace Ray
{
    using namespace std::literals;
    template <class T>
    using Object = std::unique_ptr<T>;
    template <class T>
    using Ref = std::shared_ptr<T>;
    template <class T>
    using Observer = std::experimental::observer_ptr<T>;

    template <class T, class... Args>
    constexpr Object<T> CreateObject(Args &&...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    template <class T>
    constexpr Observer<T> CreateObserver(T* val)
    {
        return std::experimental::make_observer(val);
    }
    template <class T>
    constexpr Observer<T> CreateObserver(Object<T>&& val)
    {
        return std::experimental::make_observer(val.get());
    }
    template <class T>
    constexpr Observer<T> CreateObserver(Ref<T>&& val)
    {
        return std::experimental::make_observer(val.get());
    }
}