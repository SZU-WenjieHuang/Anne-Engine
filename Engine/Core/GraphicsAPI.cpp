#include "Engine/Core/GraphicsAPI.h"

namespace GraphicsAPI
{
    /**
     * @brief 清除缓冲区到预设值。
     * 根据传入的掩码参数 `bits` 清除指定的缓冲区。
     * `bits` 可以是 `GL_COLOR_BUFFER_BIT`、`GL_DEPTH_BUFFER_BIT`、`GL_STENCIL_BUFFER_BIT` 等等。
     * 
     * @param bits 指定要清除的缓冲区。支持掩码标志的按位或组合。
     * @example
     * ClearBits(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     */
    void ClearBits(GLbitfield bits)
    {
        glClear(bits);
    }

    /**
     * @brief 指定颜色缓冲区的清除值。
     * 这个函数封装了 OpenGL 的 `glClearColor` 函数，它指定了 `glClear` 清除颜色缓冲区时使用的红、绿、蓝和 alpha 值。
     * 这些值会被限制在 [0, 1] 范围内。
     * 
     * @param red 红色值
     * @param green 绿色值
     * @param blue 蓝色值
     * @param alpha 透明度值
     */
    void ClearColor(float red, float green, float blue, float alpha)
    {
        glClearColor(red, green, blue, alpha);
    }
}