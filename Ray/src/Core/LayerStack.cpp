#include "LayerStack.hpp"

namespace Ray
{
    void LayerStack::PushLayer(const Ref<Layer> &layer)
    {
        layer->OnAttach();
        m_layers.push_back(layer);
    }
    void LayerStack::PushOverlay(const Ref<Layer> &layer)
    {
        layer->OnAttach();
        m_overlays.push_back(layer);
    }
    Ref<Layer> LayerStack::PopLayer(const Ref<Layer> &layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            auto popped_layer = *it;
            m_layers.erase(it);
            popped_layer->OnDetach();
            return popped_layer;
        }
        return Ref<Layer>(nullptr);
    }
    Ref<Layer> LayerStack::PopOverlay(const Ref<Layer> &layer)
    {
        auto it = std::find(m_overlays.begin(), m_overlays.end(), layer);
        if (it != m_overlays.end())
        {
            auto popped_overlay = *it;
            m_overlays.erase(it);
            popped_overlay->OnDetach();
            return popped_overlay;
        }
        return Ref<Layer>(nullptr);
    }

    void LayerStack::ForEachLayer(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(m_layers.begin(), m_layers.end(), func);
    }
    void LayerStack::ForEachOverlay(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(m_overlays.begin(), m_overlays.end(), func);
    }
    void LayerStack::ForEach(std::function<void(Ref<Layer> &)> func)
    {
        ForEachLayer(func);
        ForEachOverlay(func);
    }
    void LayerStack::ForEachLayerReverse(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(m_layers.rbegin(), m_layers.rend(), func);
    }
    void LayerStack::ForEachOverlayReverse(std::function<void(Ref<Layer> &)> func)
    {
        std::for_each(m_overlays.rbegin(), m_overlays.rend(), func);
    }
    void LayerStack::ForEachReverse(std::function<void(Ref<Layer> &)> func)
    {
        ForEachOverlayReverse(func);
        ForEachLayerReverse(func);
    }

    void LayerStack::OnUpdate(float deltaTime)
    {
        for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
            (*it)->OnUpdate(deltaTime);
        for (auto it = m_overlays.rbegin(); it != m_overlays.rend(); ++it)
            (*it)->OnUpdate(deltaTime);
    }

    void LayerStack::OnDetach()
    {
        ForEach([](Ref<Layer> &layer)
                { layer->OnDetach(); });
    }
}