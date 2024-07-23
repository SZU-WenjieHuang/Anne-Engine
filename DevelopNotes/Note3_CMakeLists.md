# CMakeLists内可执行文件和库的关系
CMake中可以创建可执行文件和库，并将库作为依赖项添加到可执行文件或其他库中。接下来，我将帮你梳理CMakeLists.txt中的组件和依赖关系，并解释如何使用这些组件构建项目。

### 基本概念

1. **可执行文件（Executable）**：
   - `add_executable` 用于创建可执行文件，它是最终能运行的程序。
   
2. **库（Library）**：
   - `add_library` 用于创建静态库或共享库，可以被其他项目或可执行文件链接和使用。

3. **依赖关系（Dependencies）**：
   - `add_dependencies` 用于声明目标之间的编译顺序依赖，即一个目标在另一个目标之前必须被构建。
   - `target_link_libraries` 用于链接依赖库，使目标能够使用这些库中的符号和功能。

### 示例CMakeLists.txt 结构

为了更好地理解，我将一个示例项目结构如下：

```
MyProject/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── libraryA/
│   │   ├── CMakeLists.txt
│   │   ├── libraryA.cpp
│   │   └── libraryA.h
│   └── libraryB/
│       ├── CMakeLists.txt
│       ├── libraryB.cpp
│       └── libraryB.h
└── include/
    ├── libraryA/
    │   └── libraryA.h
    └── libraryB/
        └── libraryB.h
```

### 顶层CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

# 添加子目录，构建库
add_subdirectory(src/libraryA)
add_subdirectory(src/libraryB)

# 设置目标名称
set(TARGET_NAME MyExecutable)

# 收集主源文件
file(GLOB MAIN_SRC src/main.cpp)

# 创建可执行文件
add_executable(${TARGET_NAME} ${MAIN_SRC})

# 指定依赖关系
add_dependencies(${TARGET_NAME} libraryA libraryB)

# 链接依赖库
target_link_libraries(${TARGET_NAME} PRIVATE libraryA libraryB)

# 设置全局包含路径
target_include_directories(${TARGET_NAME} PRIVATE include)
```

### src/libraryA/CMakeLists.txt

```cmake
set(LIBRARY_A_NAME libraryA)

# 收集源文件
file(GLOB LIBRARY_A_SRC libraryA.cpp)

# 创建静态库
add_library(${LIBRARY_A_NAME} STATIC ${LIBRARY_A_SRC})

# 设置该库的包含路径
target_include_directories(${LIBRARY_A_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                      ${CMAKE_CURRENT_SOURCE_DIR}/../include/libraryA)
```

### src/libraryB/CMakeLists.txt

```cmake
set(LIBRARY_B_NAME libraryB)

# 收集源文件
file(GLOB LIBRARY_B_SRC libraryB.cpp)

# 创建静态库
add_library(${LIBRARY_B_NAME} STATIC ${LIBRARY_B_SRC})

# 设置该库的包含路径
target_include_directories(${LIBRARY_B_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                      ${CMAKE_CURRENT_SOURCE_DIR}/../include/libraryB)
```

### 解释各部分的作用

1. **顶层CMakeLists.txt**：
   - `project(MyProject)`: 设置项目名称。
   - `set(CMAKE_CXX_STANDARD 17)`: 设置C++标准。
   - `add_subdirectory(src/libraryA)`: 添加子目录src/libraryA，其中包含构建`libraryA`的CMakeLists.txt。
   - `add_subdirectory(src/libraryB)`: 添加子目录src/libraryB，其中包含构建`libraryB`的CMakeLists.txt。
   - `set(TARGET_NAME MyExecutable)`: 设置目标名称为`MyExecutable`。
   - `file(GLOB MAIN_SRC src/main.cpp)`: 收集源文件`main.cpp`。
   - `add_executable(${TARGET_NAME} ${MAIN_SRC})`: 创建可执行文件`MyExecutable`。
   - `add_dependencies(${TARGET_NAME} libraryA libraryB)`: 设置库之间的依赖关系，确保`libraryA`和`libraryB`先编译。
   - `target_link_libraries(${TARGET_NAME} PRIVATE libraryA libraryB)`: 链接可执行文件依赖的库。
   - `target_include_directories(${TARGET_NAME} PRIVATE include)`: 设置全局包含路径。

2. **src/libraryA/CMakeLists.txt**：
   - 收集源文件`libraryA.cpp`。
   - 创建静态库`libraryA`。
   - 设置包含路径，使其他目标能够找到库头文件。

3. **src/libraryB/CMakeLists.txt**：
   - 收集源文件`libraryB.cpp`。
   - 创建静态库`libraryB`。
   - 设置包含路径，使其他目标能够找到库头文件。

### 总结

通过这种方式，CMakeLists.txt明确地分离了可执行文件与库之间的职责，并建立了清晰的依赖关系和包括路径配置。这种模块化的项目结构不仅便于管理和扩展，也能保证不同部分之间的独立性和可复用性。

- **可执行文件**：`add_executable` 用于创建最终的应用程序。
- **库**：`add_library` 用于创建可以被其他目标链接的模块。
- **依赖关系**：`add_dependencies` 和 `target_link_libraries` 用于确保目标间的编译顺序和符号链接。
- **包含路径**：`target_include_directories` 用于设置头文件的搜索路径，使不同模块可以共享头文件。

通过这种结构化的CMake配置，可以更有效地管理项目，并为未来的扩展提供足够的灵活性。


# CMake内的PRIVATE / PUBLIC / INTERFACE

在 CMake 中，`target_include_directories`, `target_link_libraries`, 和 `target_compile_definitions` 等命令支持 `PUBLIC`, `PRIVATE`, 和 `INTERFACE` 三种访问控制关键字。这些关键字用于定义目标（target）的属性如何传播。理解这三种关键字的关系对于正确设置项目的构建依赖关系非常重要。

### `PUBLIC`, `PRIVATE`, 和 `INTERFACE` 关系解释

1. **PRIVATE**
   - 使用 `PRIVATE` 指定的属性只在构建当前目标时生效，对依赖该目标的其他目标不可见。
   - 适用于对某个目标的内部实现有影响，但不需要被其他目标看到的依赖。

2. **PUBLIC**
   - 使用 `PUBLIC` 指定的属性不仅在构建当前目标时生效，而且会传播到所有依赖该目标的其他目标。
   - 适用于既影响当前目标本身，也影响依赖该目标的其他目标的依赖。

3. **INTERFACE**
   - 使用 `INTERFACE` 指定的属性不会直接影响当前目标，但会传播到所有依赖该目标的其他目标。
   - 适用于仅需要对外部透明，但不直接用于当前目标内部实现的依赖。

### 使用示例

假设有两个库 `LibA` 和 `LibB`，以及一个可执行文件 `MyExe`，它们之间的依赖关系如下：

- `LibB` 依赖于 `LibA`
- `MyExe` 依赖于 `LibB`

#### 定义库和可执行文件

```cmake
# 定义 LibA 库
add_library(LibA STATIC libA.cpp)
target_include_directories(LibA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 定义 LibB 库，并依赖于 LibA
add_library(LibB STATIC libB.cpp)
target_link_libraries(LibB PUBLIC LibA)
target_include_directories(LibB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libB_include)

# 定义可执行文件 MyExe，并依赖于 LibB
add_executable(MyExe main.cpp)
target_link_libraries(MyExe PRIVATE LibB)
```

### 解释各个命令的作用

#### `target_include_directories(LibA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)`

- **PUBLIC**：`LibA` 的包含目录 `${CMAKE_CURRENT_SOURCE_DIR}/include` 会传递给所有依赖 `LibA` 的目标。因此，`LibB` 和 `MyExe` 都会看到这个包含目录。

#### `target_link_libraries(LibB PUBLIC LibA)`

- **PUBLIC**：`LibB` 依赖于 `LibA`，并且这种依赖是公开的，所以任何依赖 `LibB` 的目标（如 `MyExe`）也会自动依赖于 `LibA`。

#### `target_include_directories(LibB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libB_include)`

- **PRIVATE**：`LibB` 的包含目录 `${CMAKE_CURRENT_SOURCE_DIR}/libB_include` 只在构建 `LibB` 时有效，不会传递给依赖 `LibB` 的目标。因此，这个包含目录对 `MyExe` 不可见。

#### `target_link_libraries(MyExe PRIVATE LibB)`

- **PRIVATE**：`MyExe` 依赖于 `LibB`，但是 `LibB` 的依赖不会再传播给其他目标。如果有其他目标依赖于 `MyExe`，它们不会自动依赖于 `LibB`。

### 总结

- **PUBLIC**：
  - 被指定的属性（如包含目录、链接库等）会作用于当前目标和依赖于当前目标的所有其他目标。
  - 适用于那些需要被目标本身和其依赖目标共同使用的属性。

- **PRIVATE**：
  - 被指定的属性只作用于当前目标。
  - 适用于那些仅对目标本身内部实现有影响的属性。

- **INTERFACE**：
  - 被指定的属性不会作用于当前目标，但会作用于依赖于当前目标的所有其他目标。
  - 适用于那些仅需要对外部透明，但不直接用于目标内部实现的属性。

通过合理使用这些关键字，可以更好地控制目标之间的依赖关系和构建方式，从而实现模块化、可维护的构建系统。