#include "LayerStack.hpp"

namespace Ray
{
    std::vector<Ref<Layer>> LayerStack::s_layers;
    std::vector<Ref<Layer>> LayerStack::s_overlays;

    void LayerStack::PushLayer(const Ref<Layer> &layer)
    {
        layer->OnAttach();
        s_layers.push_back(layer);
    }
    void LayerStack::PushOverlay(const Ref<Layer> &layer)
    {
        layer->OnAttach();
        s_overlays.push_back(layer);
    }
    Ref<Layer> LayerStack::PopLayer(const Ref<Layer> &layer)
    {
        auto it = std::find(s_layers.begin(), s_layers.end(), layer);
        if (it != s_layers.end())
        {
            auto popped_layer = *it;
            s_layers.erase(it);
            popped_layer->OnDetach();
            return popped_layer;
        }
        return Ref<Layer>(nullptr);
    }
    Ref<Layer> LayerStack::PopOverlay(const Ref<Layer> &layer)
    {
        auto it = std::find(s_overlays.begin(), s_overlays.end(), layer);
        if (it != s_overlays.end())
        {
            auto popped_overlay = *it;
            s_overlays.erase(it);
            popped_overlay->OnDetach();
            return popped_overlay;
        }
        return Ref<Layer>(nullptr);
    }

    void LayerStack::ForEachLayer(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(s_layers.begin(), s_layers.end(), func);
    }
    void LayerStack::ForEachOverlay(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(s_overlays.begin(), s_overlays.end(), func);
    }
    void LayerStack::ForEach(std::function<void(Ref<Layer> &)> func)
    {
        ForEachLayer(func);
        ForEachOverlay(func);
    }
    void LayerStack::ForEachLayerReverse(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(s_layers.rbegin(), s_layers.rend(), func);
    }
    void LayerStack::ForEachOverlayReverse(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(s_overlays.rbegin(), s_overlays.rend(), func);
    }
    void LayerStack::ForEachReverse(std::function<void(Ref<Layer> &)> func)
    {
        ForEachOverlayReverse(func);
        ForEachLayerReverse(func);
    }

    void LayerStack::OnUpdate(float deltaTime)
    {
        for (auto it = s_layers.rbegin(); it != s_layers.rend(); ++it)
            (*it)->OnUpdate(deltaTime);
        for (auto it = s_overlays.rbegin(); it != s_overlays.rend(); ++it)
            (*it)->OnUpdate(deltaTime);
    }

    void LayerStack::OnDetach()
    {
        ForEach([](Ref<Layer> &layer)
                { layer->OnDetach(); });
    }
}