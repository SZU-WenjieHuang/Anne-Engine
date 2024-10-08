#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Core/Serialization.h"

namespace AnneEngine
{
    namespace component
    {
        struct NameComponent
        {
            std::string name;

            NameComponent() {}
            NameComponent(const char *val) : name(val) {}
            NameComponent(std::string val) : name(val) {}
            NameComponent(std::string_view val) : name(val) {}

            // 每一个Component 都有一个序列化和反序列化的操作
            SERIALIZATION_COMPONENT_ENABLE(NameComponent, name)
            SERIALIZATION_FROM_TYPE_ANY(NameComponent)
        };

        struct ActiveComponent
        {
            bool active = true;
            SERIALIZATION_COMPONENT_ENABLE(ActiveComponent, active)
            SERIALIZATION_FROM_TYPE_ANY(ActiveComponent)
        };
    } // namespace component

    namespace global::component
    {
        struct DeltaTime
        {
            float dt;
            SERIALIZATION_COMPONENT_ENABLE(DeltaTime, dt)
            SERIALIZATION_FROM_TYPE_ANY(DeltaTime)
        };
    } // namespace global::component
}