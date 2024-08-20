#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Third/nlohmann/json.hpp"
#include "Third/entt/entt.hpp"

namespace AnneEngine
{
    namespace serialization
    {
        using BindComponentFunc = std::function<void(entt::entity &, std::shared_ptr<entt::registry> &, nlohmann::json &)>;
        using FromVoidTypeFunc = std::function<nlohmann::json(void *)>;
    }
}

// 生成不同类型的函数
// Todo

namespace glm
{
    void to_json(nlohmann::json &j, const glm::vec2 &P);
    void from_json(const nlohmann::json &j, glm::vec2 &P);
    void to_json(nlohmann::json &j, const glm::vec3 &P);
    void from_json(const nlohmann::json &j, glm::vec3 &P);
    void to_json(nlohmann::json &j, const glm::vec4 &P);
    void from_json(const nlohmann::json &j, glm::vec4 &P);
    void to_json(nlohmann::json &j, const glm::mat4 &P);
    void from_json(const nlohmann::json &j, glm::mat4 &P);
}