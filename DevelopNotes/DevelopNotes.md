# July.8 2024
Works:</br>
1.clone并编译Filament </br>
2.总结编译系统与工具的区别 </br>

# July.10 2024

### task1 编译尝试Filament
Filament构建 MacOS 直接在根文件夹下执行该命令就会启动编译
  ```sh
  ./build.sh debug
  ```
默认用ninja，没有ninja就用make，MacbookPro M2芯片大概10-25min。

  ```sh
  FILAMENT_ENABLE_LTO: Enable link-time optimizations if supported by the compiler
  FILAMENT_BUILD_FILAMAT: Build filamat and JNI buildings
  FILAMENT_SUPPORTS_OPENGL: Include the OpenGL backend
  FILAMENT_SUPPORTS_METAL: Include the Metal backend
  FILAMENT_SUPPORTS_VULKAN: Include the Vulkan backend
  FILAMENT_INSTALL_BACKEND_TEST: Install the backend test library so it can be consumed on iOS
  FILAMENT_USE_EXTERNAL_GLES3: Experimental: Compile Filament against OpenGL ES 3
  FILAMENT_SKIP_SAMPLES: Don't build sample apps
  ```
在Cmake里可以指定 使用哪个API 如Vulkan和Metal

windows内的环境搭建，可以参考这一篇 </br>
https://www.cnblogs.com/zhyan8/p/18024342

编译完成后 所有的Sample都在: </br>
[out/cmake-debug/smaples]内


### task2 ninja环境
 ```sh
  brew install ninja  
  ninja --version
  ```

### task3 运行Filament测试
gltfviwer效果
  ![alt text](assets/01.png)
helloPBR效果
  ![alt text](assets/02.png)

# July.21 2024
工作：
1. 完成Anne Engine框架搭建
2. 增加整个项目和Engine内的CMakeLists
3. 增加3Party的文件

收获：
1. 工作流程，在vscode开发，需要打断点的时候再到VisualStudio内去调试
2. CMakeLists文件 博大精深，可以定义自己的静态库，也可以link其他的静态库，include third里的头文件。这样就不需要自己再到Visual Studio内去重新link。
3. 第三方库，分成需要Header-only的，和需要link的两种。前者只需要include它的hpp，后者则需要添加进CMakeLists.txt，去执行Build。


# July.22 2024
工作:
1. 增加单例模式 Singleton的hpp文件


# July.23 2024
工作：
1. 增加Application UI的空实现。
2. 增加EditorProject的CMakeLists。
3. 学习CMakeLists文件里的，可执行文件，Library，依赖关系。以及依赖关系中的继承关系。

收获：
1. 详见 Note3的 markdown。
2. 一个可执行文件的CmakeLists，是有很好的设计模式架构的。 一个可执行文件，多个Library。 然后他们需要在CmakeLists内添加依赖关系。约定谁先被编译，谁依赖谁。
3. 在CmakeList内定义的依赖关系 也是有类似的private public interface关系，可以管理依赖的传递。


# July.24 2024
工作
1. ApplicationUI的实现(有待完成)
2. Window的实现(有待完成)
3. 增加简单的GraphicsAPI类，尚未有完整功能
4. 添加窗口类Window
5. 添加Function和GLFW相关笔记

收获
1. 关于是否需要增加Static</br>
  a. 全局函数：不需要 static 关键字，因为它们不在类内，可以直接调用。</br>
  b. 类的静态成员函数：如果你希望在不实例化类的情况下调用函数，可以使用 static 关键字。这样，函数可以通过类名直接调用，而不需要类实例。</br>
2. 关于std::shared_ptr 的markdown，以及合适需要使用enable_shared_from_this？ 其实就是增加了一个 shared_from_this 的成员函数。
3. Window类里，使用Function的别名。并且有很好的观察者模式去处理所有IO的输入。
4. Window类里，有类似LearnOpenGL的glfw的初始化和窗口创建。
5. 所有的IO回调函数，都需要被注册进GLFW里。

Todo:
1. 具体响应IO输入的函数 尚未实现（实现在ApplicationUI中）

# July.25 2024
工作
1. 学习ApplicationUI怎么组织各个Panel

收获
1. ApplicationUI负责各个Panel的管理
2. Panels内负责各个功能的实现 算是一种解耦的关系

# August.05 2024
工作
1. 发现已经有10天没做自己的引擎了，之前都一直在忙着22的新需求和工作上的事情，争取往后每天早上9:30之前，晚上21:00之后，都开始做小引擎 加油！
2. 增加Selected的相关逻辑，下一步是增加Scene

# August.12 2024 Mon

运行时查询的Inspector组件
1. 开始写Inspector组件的能力，允许用户在运行时候动态查询每一个组件的属性。
2. 每一个组件都有对应的查询函数，这个通过一个模板来实现。
3. 会非常类似于反射机制

Others
1. ImGuiFileDialog 文件查询能力
2. FontAwesome 的字体库能力

# August.13 2024 Tue

1. 完成Inspector系统的空实现，所有的component都还没具体实现 但框架有了
2. ModelPreview的空实现
3. 整理ECS框架的笔记

# August.14 2024 Wed

1. 添加对FunctionPannel的部分实现
2. 添加对Texture类的空实现
3. 添加ImGui创建窗口的笔记

# August.15 2024 Thu

1. 完成FunctionPannel类的实现，实现绘制一些FunctionPanel的能力，通过ImGui库去绘制UI(终于知道UI是怎么绘制的了 感动，也是调用基础的API能力库)
2. 添加了MeshManager类的空实现，主要是在FunctionPannel内 需要调用它的能力去展示预览模型，基本都是空实现，有待完善。是整个Mesh的绘制基础。
3. 完成Common.h内文件浏览器的实现，主要是通过ImGuiFileDialog判断有没有选中一些模型，有选中了就可以执行FileManager的Import操作。

# August.16 2024 Fri

1. 开始PanelInspector的开发
2. 研究PanelInspector中的反射机制

# August.20 2024 Tue

1. 这个周末在忙很多事情 错过了几天的引擎开发 今日继续
2. 过程中 发现Panel 严重依赖 SceneManager -> Scene -> Entity -> Serialization
3. 先完善一下 Entity 和 Serialization，再继续开发Panel
4. 添加引擎内需要的 反序列化和序列化笔记

# August.21 2024 Wed

1. 完善Entity组件，主要是序列化相关的代码
2. 开始完善Entity类
3. 添加对于Entity的Registry的笔记 (感觉主要像是ptr 和一个全局唯一标识)


# August.22 2024 Thu

1. 完善Component类和Entity类


# August.23 2024 Fri

1. 完善Scene类，和Inspector类


# September.05 2024 Thu

1. 上周工作忙了很多，一下子多了很多并行的需求和任务
2. 这周开始，继续完善！ Scene类和Inspector类要开发完，ECS模式的UI框架。
3. 完成Scene类
4. 完成Inspector类
5. 明天可以开始PannelPreference类的开发