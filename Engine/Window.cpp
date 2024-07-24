#include "Engine/Window.h"
#include <iostream>
using namespace AnneEngine;

namespace AnneEngine::io
{
    // 定义io事件回调函数的容器
    static std::vector<onResetFunc> onResetFuncVecs;
    static std::vector<onKeyFunc> onKeyFuncVecs;
    static std::vector<onMouseButtonFunc> onMouseButtonFuncVecs;
    static std::vector<onCursorPosFunc> onCursorPosFuncVecs;
    static std::vector<onWindowSizeFunc> onWindowSizeFuncVecs;
    static std::vector<onScrollFunc> onScrollFuncVecs;

    // 观察者模式 调用每一个注册进来的回调函数
    void GLFWImplCallbackOnReset(GLFWwindow* window)
    {
        for (auto& func : onResetFuncVecs)
        {
            func();
        }   
    }
    void GLFWImplCallbackOnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        for (auto& func : onKeyFuncVecs)
        {
            func(key, scancode, action, mods);
        }
    }
    void GLFWImplCallbackOnMouseButton(GLFWwindow* window, int button, int action, int mods)
    {
        for (auto& func : onMouseButtonFuncVecs)
        {
            func(button, action, mods);
        }
    }
    void GLFWImplCallbackOnCursorPos(GLFWwindow* window, double xpos, double ypos)
    {
        for (auto& func : onCursorPosFuncVecs)
        {
            func(xpos, ypos);
        }
    }
    void GLFWImplCallbackOnWindowSize(GLFWwindow* window, int width, int height)
    {
        for (auto& func : onWindowSizeFuncVecs)
        {
            func(width, height);
        }
    }
    void GLFWImplCallbackOnScroll(GLFWwindow* window, double xoffset, double yoffset)
    {
        for (auto& func : onScrollFuncVecs)
        {
            func(xoffset, yoffset);
        }
    }
}


EngineWindow::EngineWindow(EngineWindow::Size size, std::string_view title, int32_t major_version, int32_t minor_version)
    : m_size(size)
{
    // glfw初始化设置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    m_window = glfwCreateWindow(size.width, size.height, title.data(), nullptr, nullptr);
    if (m_window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // 设置上下文
    glfwMakeContextCurrent(m_window);

    // GLAD加载
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // 设置光标可以正常移动
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

EngineWindow::~EngineWindow()
{
}

GLFWwindow* EngineWindow::GetWindow()
{
    return m_window;
}

EngineWindow::Size EngineWindow::GetSize()
{
    return m_size;
}

void EngineWindow::Resize(unsigned int width, unsigned int height)
{
    m_size.width = width;
    m_size.height = height;
    RescaleViewport();
}

void EngineWindow::RescaleViewport()
{
    glViewport(0, 0, m_size.width, m_size.height);
}

// 向glfw窗口注册IO事件回调函数
void EngineWindow::RegisterIO()
{
    glfwSetFramebufferSizeCallback(m_window, io::GLFWImplCallbackOnWindowSize);
    glfwSetKeyCallback(m_window, io::GLFWImplCallbackOnKey);
    glfwSetMouseButtonCallback(m_window, io::GLFWImplCallbackOnMouseButton);
    glfwSetCursorPosCallback(m_window, io::GLFWImplCallbackOnCursorPos);
    glfwSetScrollCallback(m_window, io::GLFWImplCallbackOnScroll);  
}

// 向glfw窗口注册重置回调函数(直接添加到Vector内)
void EngineWindow::RegisterOnResetFunc(io::onResetFunc func)
{
    io::onResetFuncVecs.push_back(func);
}
void EngineWindow::RegisterOnKeyFunc(io::onKeyFunc func)
{
    io::onKeyFuncVecs.push_back(func);
}
void EngineWindow::RegisterOnMouseButtonFunc(io::onMouseButtonFunc func)
{
    io::onMouseButtonFuncVecs.push_back(func);
}
void EngineWindow::RegisterOnCursorPosFunc(io::onCursorPosFunc func)
{
    io::onCursorPosFuncVecs.push_back(func);
}
void EngineWindow::RegisterOnReSizeFunc(io::onWindowSizeFunc func)
{
    io::onWindowSizeFuncVecs.push_back(func);
}
void EngineWindow::RegisterOnScrollFunc(io::onScrollFunc func)
{
    io::onScrollFuncVecs.push_back(func);
}

// swaps buffers
void EngineWindow::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

// Poll events 处理所有挂起的事件，并更新窗口的状态
void EngineWindow::PollEvents()
{
    glfwPollEvents();
}

// Shoulde close 判断窗口是否应该关闭
bool EngineWindow::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

// Terminate 销毁窗口
void EngineWindow::Terminate()
{
    glfwTerminate();
}







