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
Todo: </br>
[UI] 整体框架，界面，显示窗口
