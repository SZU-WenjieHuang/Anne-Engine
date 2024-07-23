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
    };

    template <typename T>
    T &Singleton<T>::Instance()
    {
        static std::unique_ptr<T> _instance{new T{token{}}};  // unique_ptr 创建单例
        return *_instance;
    }
}