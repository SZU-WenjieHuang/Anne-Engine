#pragma once
#include <memory>
#include "Engine/Core/GraphicsAPI.h"

namespace AnneEngine
{
    class TextureBase;

    namespace Texture
    {

    }

    // 暂时空实现
    class TextureBase
    {
    protected:
        GLuint m_id;
        int m_width, m_height, m_tmp_slot;

    public:
        inline GLuint GetID() const { return m_id; }
    };
}