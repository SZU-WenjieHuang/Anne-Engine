#pragma once
#include "Engine/AnneEngine.h"

namespace AnneEngine
{
    namespace Application
    {
        class Selected : public Singleton<Selected>
        {
            private:

            public:
                Selected() = delete;
                Selected(token){}
                Scene::Node::Ptr node{nullptr};
        };
    }
} // namespace AnneEngine
