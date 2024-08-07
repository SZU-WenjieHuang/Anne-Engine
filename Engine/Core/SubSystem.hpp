#pragma once
#include <gtc/type_ptr.hpp>
#include <string>
#include <string_view>
#include <memory>
#include <array>
#include <vector>

namespace AnneEngine
{
    /// @brief 子系统 虚函数:Init(),Update()
    class SubSystem : public std::enable_shared_from_this<SubSystem>
    {
    public:
        SubSystem() = default;
        virtual ~SubSystem()
        {
        }

        virtual void Init() = 0;
        virtual void Update() = 0;
    };
}


