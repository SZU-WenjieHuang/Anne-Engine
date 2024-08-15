#pragma once
#include "Engine/Function/Graphics/Texture/TextureBase.h"

namespace AnneEngine
{
    // 暂时空实现
    class Texture2D : public TextureBase
    {
    public:
        using Ptr = std::shared_ptr<Texture2D>;
        
    };

    class Texture3D : public TextureBase
    {

    };
}