#pragma once
#include <string>
#include <string_view>
#include <memory>
#include <array>
#include <vector>
#include <unordered_map>
#include <functional>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace AnneEngine
{
    template <typename T>
    class Singleton
    {
    public:
        static T &Instance();  // 通过Instance 访问全局唯一实例

        Singleton(const Singleton &) = delete;  // 删除拷贝构造
        Singleton &operator=(const Singleton) = delete;   // 删除拷贝赋值

    protected:
        struct token
        {
        };
        Singleton(){} // Singleton的构造 + 构造的入参token 放在protected内
        /*
        空结构体 token: 通过传递一个空的 token 实例（token{}）到构造函数，
        允许内部代码（例如 Instance() 方法）调用该构造函数。
        而外部代码因为不知道 token 的存在（或者说它的具体结构和作用），
        因此不能直接创建 Singleton 的实例。
        */
    };

    template <typename T>
    T &Singleton<T>::Instance()
    {
        static std::unique_ptr<T> _instance{new T{token{}}};  // unique_ptr 创建单例
        return *_instance;
    }
}