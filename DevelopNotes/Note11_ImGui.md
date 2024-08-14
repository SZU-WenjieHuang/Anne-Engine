ImGui（Immediate Mode GUI）是一个非常流行的图形用户界面库，常用于游戏和应用程序的工具界面。下面我将详细解释如何使用ImGui创建窗口和控制窗口。

### ImGui的基本概念

ImGui是“立即模式”图形用户界面库，这意味着界面元素的状态和绘制过程在每一帧中都是即时的。你每次更新界面时，都会重新定义控件的状态。

### 创建窗口

使用ImGui创建一个窗口非常简单，以下是一个基本示例：

```cpp
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions

// GLFW和OpenGL初始化代码省略

// 主循环
while (!glfwWindowShouldClose(window))
{
    // 处理输入
    glfwPollEvents();

    // 开始新帧
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 创建窗口
    {
        ImGui::Begin("My First Window"); // 开始窗口

        ImGui::Text("Hello, world!");    // 添加文本
        if (ImGui::Button("Click Me!"))  // 添加按钮
        {
            // 按钮被点击时的逻辑
        }

        ImGui::End(); // 结束窗口
    }

    // 渲染
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}
```

### 控制窗口

ImGui提供了一些函数来控制窗口的行为：

1. **设置窗口大小和位置**
   ```cpp
   ImGui::SetWindowSize("My First Window", ImVec2(300, 200)); // 设置窗口尺寸
   ImGui::SetWindowPos("My First Window", ImVec2(50, 50));   // 设置窗口位置
   ```

2. **可拖动和可关闭的窗口**
   ```cpp
   ImGui::Begin("My Draggable Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
   ```

3. **隐藏和显示窗口**
   ```cpp
   if (show_window) {
       ImGui::Begin("Toggle Window");
   }
   else {
       ImGui::End();
   }
   ```

4. **自动调整窗口大小**
   ```cpp
   ImGui::SetWindowCollapsed("My First Window", true); // 折叠窗口
   ImGui::SetWindowFocus("My First Window"); // 将焦点设置到窗口
   ```

### 处理用户输入

你可以通过按钮、滑块、文本框等控件来处理用户输入。在窗口内部使用不同的控件来获取和设置数据。

```cpp
static float value = 0.0f;
ImGui::SliderFloat("Float Slider", &value, 0.0f, 1.0f); // 创建滑动条
```

这两个枚举定义分别与 ImGui 的窗口条件和窗口标志库相关联。

### 1. `ImGuiCond_` 枚举
这是一个用于设置窗口或控件变量的条件标记。每个条件影响变量设置的行为。

- **ImGuiCond_None** / **ImGuiCond_Always**: 无条件，始终设置变量。
- **ImGuiCond_Once**: 只在程序运行期间第一次调用时设置变量。
- **ImGuiCond_FirstUseEver**: 当窗口或控件首次使用时（没有在 .ini 文件中保存数据）设置变量。
- **ImGuiCond_Appearing**: 当窗口从隐藏状态或不活跃状态变为可见时设置变量。

### 使用场景
这些条件可以用于控制窗口或控件的行为，比如布局、位置、状态等。例如，使用 `ImGuiCond_FirstUseEver` 可以只在首次使用时设置窗口的位置，避免每次重启程序时都重置。

### 2. `ImGuiWindowFlags_` 枚举
这个枚举定义了窗口的各种属性和标志，影响窗口的外观和交互行为。

一些常见标志包括：
- **ImGuiWindowFlags_NoTitleBar**: 禁用标题栏。
- **ImGuiWindowFlags_NoResize**: 禁止用户调整窗口大小。
- **ImGuiWindowFlags_NoMove**: 禁止用户移动窗口。
- **ImGuiWindowFlags_AlwaysAutoResize**: 确保窗口每帧自动调整大小以适应内容。
- **ImGuiWindowFlags_NoScrollWithMouse**: 禁用用户使用鼠标滚轮滚动窗口的功能。

### 使用场景
这些标志可以根据你所需的 UI 设计来配置窗口。例如，如果你想创建一个只用于展示信息的窗口，可以使用 `ImGuiWindowFlags_NoTitleBar` 和 `ImGuiWindowFlags_NoResize` 等标志，确保窗口不被用户随意改变。
