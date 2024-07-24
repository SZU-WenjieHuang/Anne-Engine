#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Core/GraphicsAPI.h"
#include "GLFW/glfw3.h"

namespace AnneEngine
{
    namespace io
    {
        // 窗口回调函数的签名
        using onResetFunc = std::function<void()>;  // 重置
        using onKeyFunc = std::function<void(int, int, int, int)>; // 键盘按压
        using onMouseButtonFunc = std::function<void(int, int, int)>; // 鼠标点击
        using onCursorPosFunc = std::function<void(double, double)>; // 光标移动
        using onScrollFunc = std::function<void(double, double)>; // 鼠标滚轮
        using onWindowSizeFunc = std::function<void(int, int)>; // 窗口事件
    }

    // 一个类继承 std::enable_shared_from_this<ClassName> 时，这会为该类添加一个 shared_from_this 成员函数
    // 合适需要在类的内部成员函数中创建一个指向自身的 std::shared_ptr的场景
    class EngineWindow : public std::enable_shared_from_this<EngineWindow>
    {

    };
}

