#pragma once

#include "Engine/Core/Singleton.hpp"
#include "Engine/Function/Graphics/Texture/All.h"
#include "Engine/Function/Graphics/MeshManager.h"

namespace AnneEngine
{
    class Engine : public Singleton<Engine>
    {
    public:
        Engine() = delete;
        Engine(token){};
    };
}