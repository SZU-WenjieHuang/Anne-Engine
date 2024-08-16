#pragma once
#include "Engine/Core/Singleton.hpp"

namespace AnneEngine
{
    class Scene
    {
    public:
        struct Setting
        {

        };
        
        struct Node
        {
            using Ptr = std::shared_ptr<Scene::Node>;

        };
        
    };
}