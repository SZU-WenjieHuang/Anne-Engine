# Std::Function

常用与回调函数等，需要把一个函数当作参数传递的时候

`std::function` 是 C++11 引入的一个标准库模板类，用于封装可调用对象。一个可调用对象可以是普通的函数、lambda 表达式、函数指针或其它重载了 `operator()` 的类对象（如 `std::bind` 所返回的对象）。`std::function` 提供了一种统一的方式来存储和调用这些可调用对象。

以下是一些 `std::function` 的主要特性和用途：

1. **类型安全的可调用对象封装器**：
   `std::function` 可以存储任何符合其签名（返回类型和参数类型）的可调用对象。

2. **方便的存储和传递回调函数**：
   使用 `std::function` 你可以将回调函数存储在容器中或在不同函数之间传递。

3. **支持多种可调用对象**：
   `std::function` 支持普通函数、成员函数、lambda 表达式，以及 `std::bind` 和函数对象。

4. **RAII（资源获取即初始化）**：
   `std::function` 会管理其内部所持有的可调用对象的生命周期，当 `std::function` 对象销毁时，会自动释放任何内部资源。

下面是一个简单的示例说明如何使用 `std::function`：

```cpp
#include <iostream>
#include <functional>

// 定义一个接受 std::function 的函数
void callFunction(std::function<void(int)> func, int value) {
    func(value);
}

// 普通的全局函数
void printValue(int x) {
    std::cout << "Value: " << x << std::endl;
}

int main() {
    // 使用普通函数
    std::function<void(int)> func1 = printValue;
    callFunction(func1, 42);

    // 使用 lambda 表达式
    std::function<void(int)> func2 = [](int x) {
        std::cout << "Lambda value: " << x << std::endl;
    };
    callFunction(func2, 42);

    // 使用 std::bind 绑定成员函数
    struct Foo {
        void print(int x) {
            std::cout << "Foo::print value: " << x << std::endl;
        }
    };

    Foo foo;
    std::function<void(int)> func3 = std::bind(&Foo::print, foo, std::placeholders::_1);
    callFunction(func3, 42);

    return 0;
}
```

在这个例子中，我们展示了如何使用 `std::function` 来封装和调用一个普通函数、一个 lambda 表达式和一个绑定的成员函数。

你的代码片段定义了一些 `std::function` 类型别名，展示了如何使用它们来处理各种回调。例如：

- `onResetFunc` 用于存储一个无参数且无返回值的回调函数。
- `onKeyFunc` 用于存储一个接受四个 `int` 参数的回调函数。
- `onMouseButtonFunc` 用于存储一个接受三个 `int` 参数的回调函数。
- `onCursorPosFunc` 用于存储一个接受两个 `double` 参数的回调函数。
- `onScrollFunc` 用于存储一个接受两个 `double` 参数的回调函数。
- `onWindowSizeFunc` 用于存储一个接受两个 `int` 参数的回调函数。

这些类型别名通常用于事件驱动编程，方便地登记和调用各种事件处理器。