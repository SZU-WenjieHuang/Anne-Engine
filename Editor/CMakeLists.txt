# set peoject name
set(TARGET_NAME Editor)
project(${TARGET_NAME})

# Collect files in Editor project
file(GLOB APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Application/*.cpp)
file(GLOB APP_INSPECTOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Application/Inspector/*.cpp)
file(GLOB APP_GIZMO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Application/Gizmo/*.cpp)
file(GLOB APP_FILE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Application/FileBrowser/*.cpp)
file(GLOB APP_VIS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Application/Visualization/*.cpp)
file(GLOB CONFIG_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp)
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

list(APPEND EDITOR_SOURCES
    ${APP_SRC}
    ${APP_INSPECTOR_SRC}
    ${APP_GIZMO_SRC}
    ${APP_FILE_SRC}
    ${APP_VIS_SRC}
    ${CONFIG_SRC}
    ${MAIN_SRC}
)

# Add Executable 可执行文件 Editor
add_executable(${TARGET_NAME} ${EDITOR_SOURCES})

# Add Dependencies 添加依赖库 是Engine对应的Library
add_dependencies(${TARGET_NAME} Engine)

# 添加第三方库 imgui 和 engine
target_link_libraries(${TARGET_NAME} PUBLIC imgui Engine)
target_include_directories(${TARGET_NAME} PUBLIC ${ROOT_DIR}/)

# Imgui Header
target_include_directories(${TARGET_NAME} PUBLIC ${ROOT_DIR}/Third/imgui)
target_include_directories(${TARGET_NAME} PUBLIC ${ROOT_DIR}/Third/imgui/backends)

# copy editor's shader 复制shader到output文件夹下
add_custom_target(copy_editor_shader ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Application/Shader
    ${OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/Resource/Shader/Editor
)

# copy editor's images source 复制resource到output文件夹下
add_custom_target(copy_editor_images ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Images
    ${OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/Images
)