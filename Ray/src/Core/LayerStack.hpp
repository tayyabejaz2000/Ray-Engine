#pragma once

#include "Core/Core.hpp"
#include "Layer.hpp"

namespace Ray
{
    class RAYAPI LayerStack
    {
    public:
        void PushLayer(const Ref<Layer> &);
        void PushOverlay(const Ref<Layer> &);
        Ref<Layer> PopLayer(const Ref<Layer> &);
        Ref<Layer> PopOverlay(const Ref<Layer> &);

        inline std::vector<Ref<Layer>> &GetLayers() { return m_layers; }
        inline std::vector<Ref<Layer>> &GetOverlays() { return m_overlays; }

        void ForEach(std::function<void(Ref<Layer> &)>);
        void ForEachLayer(std::function<void(Ref<Layer> &)>);
        void ForEachOverlay(std::function<void(Ref<Layer> &)>);
        void ForEachReverse(std::function<void(Ref<Layer> &)>);
        void ForEachLayerReverse(std::function<void(Ref<Layer> &)>);
        void ForEachOverlayReverse(std::function<void(Ref<Layer> &)>);

        void OnUpdate(float);
        void OnDetach();

    private:
        std::vector<Ref<Layer>> m_layers;
        std::vector<Ref<Layer>> m_overlays;
    };
}