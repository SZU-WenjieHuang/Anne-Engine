#pragma once
#include "Engine/AnneEngine.h"

namespace AnneEngine
{
    namespace inspection
    {
        class ModelPreview
        {
        public:
            static void Init();
            static void Delete(std::string name);
            static void Add(std::string name);
            // inline static std::unordered_map<std::string, WriteToTexture::Ptr> &GetAllResults(){ return m_preview_results;};  

        private:
            const static int m_preview_size = 256;
            // inline static std::unordered_map<std::string, WriteToTexture::Ptr> m_preview_results{};
            // inline static ShaderProgram::Ptr m_shader{nullptr};  
        };
    }
}