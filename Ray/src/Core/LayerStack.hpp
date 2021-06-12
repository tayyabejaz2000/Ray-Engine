#pragma once

#include "Core/Core.hpp"
#include "Layer.hpp"

namespace Ray
{
    class RAYAPI LayerStack
    {
    public:
        static void PushLayer(const Ref<Layer> &);
        static void PushOverlay(const Ref<Layer> &);
        static Ref<Layer> PopLayer(const Ref<Layer> &);
        static Ref<Layer> PopOverlay(const Ref<Layer> &);

        static inline std::vector<Ref<Layer>> &GetLayers() { return s_layers; }
        static inline std::vector<Ref<Layer>> &GetOverlays() { return s_overlays; }

        static void ForEach(std::function<void(Ref<Layer> &)>);
        static void ForEachLayer(std::function<void(Ref<Layer> &)>);
        static void ForEachOverlay(std::function<void(Ref<Layer> &)>);
        static void ForEachReverse(std::function<void(Ref<Layer> &)>);
        static void ForEachLayerReverse(std::function<void(Ref<Layer> &)>);
        static void ForEachOverlayReverse(std::function<void(Ref<Layer> &)>);

        static void OnUpdate(float);
        static void OnDetach();

    private:
        static std::vector<Ref<Layer>> s_layers;
        static std::vector<Ref<Layer>> s_overlays;
    };
}