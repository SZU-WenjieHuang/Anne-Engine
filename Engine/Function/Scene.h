#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Function/Entity.h"

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
            glm::mat4 model{1.0f};
            Entity::Ptr object{nullptr}; 

        };

    public:
        using Ptr = std::shared_ptr<Scene>;
        using Index = unsigned int;

    public:
        inline Node::Ptr &GetRootNode() { return m_root; }

    private:
        Node::Ptr m_root;
    };
}