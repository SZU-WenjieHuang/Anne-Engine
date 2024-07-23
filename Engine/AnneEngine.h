#pragma once

#include "Engine/Core/Singleton.hpp"
namespace AnneEngine
{
    class Engine : public Singleton<Engine>
    {
    public:
        Engine() = delete;
        Engine(token){};
    };
}