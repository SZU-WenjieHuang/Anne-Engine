# std::shared_ptr
`std::shared_ptr` 是 C++11 引入的智能指针之一，用于管理动态分配对象的资源。它允许多个指针共享同一个对象，并自动管理对象的生命周期。当最后一个 `std::shared_ptr` 指针离开作用域时，对象会被自动删除，避免了手动管理内存导致的资源泄漏和悬空指针问题。

### 基本概念

1. **创建和初始化**：
   - 可以通过 `std::make_shared` 也可以通过原始指针创建 `std::shared_ptr` 对象。
2. **复制和共享所有权**：
   - 复制一个 `std::shared_ptr` 会增加引用计数，共享所有权。
3. **转让所有权**：
   - 当一个 `std::shared_ptr` 被赋值到另一个时，原来的指针所有权会被转让。
4. **引用计数**：
   - `std::shared_ptr` 维护一个引用计数，用于跟踪有多少个 `shared_ptr` 对象指向同一个对象。
5. **自定义删除器**：
   - 可以使用自定义删除器来定义释放资源的方式。

### 基本用法示例

#### 创建和初始化

##### 使用 `std::make_shared`

这是创建 `std::shared_ptr` 最推荐的方式，因为它在单个操作中动态分配对象和控制块（用于引用计数），性能较高且更安全。

```cpp
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int value) : value(value) {
        std::cout << "MyClass constructed with value: " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructed with value: " << value << std::endl;
    }
    int value;
};

void example_make_shared() {
    // 使用 std::make_shared 创建 shared_ptr
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(42);
    std::cout << "Value in shared_ptr: " << ptr->value << std::endl;
}
```

#### 使用原始指针创建 `std::shared_ptr`

```cpp
void example_raw_pointer() {
    // 通过原始指针创建 shared_ptr
    MyClass *raw_ptr = new MyClass(84);
    std::shared_ptr<MyClass> ptr(raw_ptr);
    std::cout << "Value in shared_ptr: " << ptr->value << std::endl;
}
```

#### 复制和共享所有权

```cpp
void example_copying() {
    // 使用 std::make_shared 创建 shared_ptr
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(21);

    // 复制 shared_ptr 会增加引用计数
    std::shared_ptr<MyClass> ptr2 = ptr1;
    std::cout << "Use count: " << ptr1.use_count() << std::endl;  // 输出: 2

    // 修改其中一个指针，另一个指针也能看到更改
    ptr2->value = 99;
    std::cout << "Value in ptr1: " << ptr1->value << std::endl;  // 输出: 99
}
```

#### 转让所有权

```cpp
void example_transfer_ownership() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(63);

    // 通过赋值转让所有权
    std::shared_ptr<MyClass> ptr2 = std::move(ptr1);
    std::cout << "Use count: " << ptr2.use_count() << std::endl;  // 输出: 1
    // ptr1 现在为空
    std::cout << "ptr1 is null: " << std::boolalpha << (ptr1 == nullptr) << std::endl;  // 输出: true
}
```

#### 自定义删除器

你可以自定义 `shared_ptr` 在对象生命周期结束时如何删除对象。例如，如果你的对象需要特殊的清理步骤或者你在使用一个不通过 `delete` 删除的资源。

```cpp
void custom_deleter(MyClass* ptr) {
    std::cout << "Custom deleter for MyClass with value: " << ptr->value << std::endl;
    delete ptr;
}

void example_custom_deleter() {
    // 创建 shared_ptr 并指定自定义删除器
    std::shared_ptr<MyClass> ptr(new MyClass(27), custom_deleter);
}
```

### 详细示例

#### 示例：资源管理

假设你在管理一个文件资源，确保文件在程序生命周期内不被重复打开或者忘记关闭。

```cpp
#include <iostream>
#include <fstream>
#include <memory>

class FileCloser {
public:
    void operator()(std::fstream* fs) const {
        if (fs) {
            fs->close();
            std::cout << "File closed" << std::endl;
        }
        delete fs;
    }
};

void file_management_example() {
    // 使用 std::shared_ptr 管理文件资源，并指定自定义删除器
    std::shared_ptr<std::fstream> file(new std::fstream("example.txt", std::ios::out), FileCloser());
    
    if (file->is_open()) {
        *file << "Hello, world!" << std::endl;
    }
}
```

在这个例子中，我们使用自定义删除器 `FileCloser` 确保文件在 `shared_ptr` 离开作用域时自动关闭。

#### 示例：类中的 `shared_from_this`

这里展示了如何在类的成员函数中创建一个指向自身的 `shared_ptr`，确保安全且正确地管理对象生命周期。

```cpp
#include <iostream>
#include <memory>

class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    MyClass(int value) : value(value) {
        std::cout << "MyClass constructed with value: " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructed with value: " << value << std::endl;
    }

    std::shared_ptr<MyClass> GetShared() {
        return shared_from_this();
    }

    void PrintSelf() const {
        std::cout << "MyClass: value = " << value << std::endl;
    }

private:
    int value;
};

void shared_from_this_example() {
    std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(42);
    std::shared_ptr<MyClass> another_ptr = ptr->GetShared();

    std::cout << "Use count: " << ptr.use_count() << std::endl;  // 输出: 2
    another_ptr->PrintSelf();
}

int main() {
    // 调用不同示例函数展示 shared_ptr 的用法
    example_make_shared();
    example_raw_pointer();
    example_copying();
    example_transfer_ownership();
    example_custom_deleter();
    file_management_example();
    shared_from_this_example();

    return 0;
}
```

### 总结

- `std::shared_ptr` 提供了一种智能且安全的方式管理动态分配的资源。
- 它允许多个 `shared_ptr` 对象共享同一个资源，并自动管理其生命周期。
- 通过合理使用构造函数、复制和移动语义、自定义删除器等功能，可以有效地避免内存泄漏和悬空指针等问题。

希望这些示例和解释对你理解 `std::shared_ptr` 有所帮助。如果你需要更多信息或者有进一步的问题，请随时提问。


# 更多关于enable_shared_from_this
详细解释一下。`std::enable_shared_from_this<EngineWindow>` 并不是把 `EngineWindow` 定义为一个 `shared_ptr` 智能指针对象，而是提供了使 `EngineWindow` 类能够安全地创建指向自身的 `shared_ptr` 的机制。

### 详细解释

### `std::enable_shared_from_this`

当一个类继承 `std::enable_shared_from_this<ClassName>` 时，这会为该类添加一个 `shared_from_this` 成员函数(重点)。这个成员函数可以用于从类的成员函数中创建一个指向当前对象的 `std::shared_ptr`。

### 为什么需要 `shared_from_this`

1. **安全性理由**：
   - 直接使用 `std::shared_ptr(this)` 来创建一个 `shared_ptr` 会导致隐晦的错误，因为这可能会创建一个新的控制块。这意味着多次使用 `shared_ptr(this)` 可能会有多个独立的引用计数，这会导致对象被多次删除，进而导致未定义行为。

2. **共享引用计数**：
   - `shared_from_this` 在已有的 `shared_ptr` 基础上创建一个新的 `shared_ptr`，这保证了所有 `shared_ptr` 对象共享同一个引用计数，确保对象只被删除一次。

### 如何使用 `enable_shared_from_this`

`define_shared_from_this` 提供了一种安全的方法，可以在类内部获取指向自身的 `shared_ptr`，并确保引用计数正确。

### 示例代码

让我们详细地看一下如何在一个类中使用 `enable_shared_from_this`。

```cpp
#include <iostream>
#include <memory>

class EngineWindow : public std::enable_shared_from_this<EngineWindow> {
public:
    EngineWindow(int id) : id(id) {
        std::cout << "EngineWindow created with id: " << id << std::endl;
    }

    ~EngineWindow() {
        std::cout << "EngineWindow destroyed with id: " << id << std::endl;
    }

    // 获取指向自身的 shared_ptr
    std::shared_ptr<EngineWindow> GetShared() {
        return shared_from_this();
    }

    void Identify() {
        std::cout << "I am EngineWindow with id: " << id << std::endl;
        // 在成员函数中获取自身的 shared_ptr
        std::shared_ptr<EngineWindow> self = shared_from_this();
        std::cout << "Shared pointer use count: " << self.use_count() << std::endl;
    }

private:
    int id;
};

int main() {
    // 创建一个 EngineWindow 的 shared_ptr
    std::shared_ptr<EngineWindow> window = std::make_shared<EngineWindow>(1);

    // 调用 Identify 方法，验证引用计数
    window->Identify();

    // 获取一个新的 shared_ptr，引用相同的对象
    std::shared_ptr<EngineWindow> another_window = window->GetShared();
    std::cout << "Use count after GetShared: " << another_window.use_count() << std::endl;

    return 0;
}
```

### 输出

```
EngineWindow created with id: 1
I am EngineWindow with id: 1
Shared pointer use count: 2
Use count after GetShared: 2
EngineWindow destroyed with id: 1
```

### 解释

1. **创建 `std::shared_ptr`**：
   - `std::make_shared<EngineWindow>(1)` 创建了一个 `EngineWindow` 对象并返回一个 `std::shared_ptr`，初始引用计数为 1。

2. **调用 `Identify` 方法**：
   - 在 `Identify` 方法中调用 `shared_from_this` 获取指向自身的 `shared_ptr`，增加了引用计数，因此在方法内部引用计数变为 2。

3. **调用 `GetShared` 方法**：
   - 通过 `GetShared` 方法返回了一个新的 `std::shared_ptr`，引用计数继续保持 2。

4. **析构对象**：
   - `main` 函数结束时，两个 `shared_ptr` 离开作用域，引用计数变为 0，自动销毁 `EngineWindow` 对象。

### 总结

- **`std::enable_shared_from_this`** 允许类的成员函数在安全的上下文中创建 `std::shared_ptr`。
- **引用计数管理**：通过 `shared_from_this` 创建的 `shared_ptr` 共享相同的引用计数，从而确保对象只会在没有任何 `shared_ptr` 引用它时被销毁。
- **使用场景**：比较合适的时机在于当你需要在类的内部成员函数中创建一个指向自身的 std::shared_ptr，以确保对象的生命周期被正确管理。这种情况下，std::enable_shared_from_this 可以帮助你避免直接使用 this 指针生成 shared_ptr 所带来的潜在风险（如双重释放等问题）。

希望这些解释和示例能帮助你更好地理解 `std::enable_shared_from_this` 及其在 `shared_ptr` 管理中的作用。如果有任何进一步的问题或需要更多示例，请随时提问。