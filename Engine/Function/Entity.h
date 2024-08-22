// 暂时定义一个空的接口头文件

#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Core/SubSystem.hpp"
#include "Third/entt/entt.hpp"
#include "Engine/Core/Serialization.h"
#include "Engine/Function/Component/Component.h"
#include <iostream>

namespace AnneEngine
{
    /**
     * @brief Entity的序列化与反序列化函数 
    */
    class ComponentSerilizationMap
    {
        friend class ComponentRegisterationMap;

    private:
        inline static std::unordered_map<entt::id_type, std::string> idtype_to_name;                          // 从id到名字
        inline static std::unordered_map<entt::id_type, serialization::FromVoidTypeFunc> idtype_to_regFunc;   // 序列化函数
        inline static std::unordered_map<std::string, serialization::BindComponentFunc> str_to_bindFunc;      // 反序列化函数
    
    public:
        inline static std::string GetName(entt::id_type id) { return idtype_to_name[id]; }
        inline static nlohmann::json GetJsonFromVoidType(entt::id_type id, void *typeAny) { return idtype_to_regFunc[id](typeAny); }
        inline static serialization::BindComponentFunc &GetBindFunc(std::string &componentType) { return str_to_bindFunc[componentType]; }       
    };

    /**
     * @brief 默认Registry, 构造Entity时不传入Registry参数则使用EntityDefaultRegistry进行默认构造
     * */ 
    class EntityDefaultRegistry : public Singleton<EntityDefaultRegistry>
    {
    private:
        std::shared_ptr<entt::registry> default_register{nullptr};

    public:
        EntityDefaultRegistry() = delete;
        EntityDefaultRegistry(token) { default_register = std::make_shared<entt::registry>(); }

        inline void SwitchDefaultRegistry(std::shared_ptr<entt::registry> &&new_reg) 
        {
            default_register = std::forward<std::shared_ptr<entt::registry>>(new_reg); // forward 完美转发
        }

        inline std::shared_ptr<entt::registry> GetRegistry() 
        {
            return default_register; 
        }
    };

    /// @brief 实体
    class Entity
    {

    public:
        using Ptr = std::shared_ptr<Entity>;

        Entity()
        {
            m_registry = EntityDefaultRegistry::Instance().GetRegistry();
            m_entity = m_registry->create();
        }

        Entity(std::shared_ptr<entt::registry> &regs)
        {
            m_registry = regs;
            m_entity = m_registry->create();
        }

        void Destroy();
        bool Valid();
        bool IsActive();
        void SetActive(bool active);

    public:
         // 01 默认create
        inline static Entity::Ptr Create()
        {
            return std::make_shared<Entity>();
        }

        // 02 用registryCreate
        inline static Entity::Ptr Create(std::shared_ptr<entt::registry> &regs)
        {
            return std::make_shared<Entity>(regs); // 传入registry的 create
        }

        // 03 添加名字为name的component
        inline static Entity::Ptr Create(std::string_view name)
        {
            auto _ptr = std::make_shared<Entity>();
            _ptr->AddComponent<component::NameComponent>(name);
            return _ptr;
        }

        // 04 用registryCreate + 添加名字为name的component
        inline static Entity::Ptr Create(std::string_view name, std::shared_ptr<entt::registry> &regs)
        {
            auto _ptr = std::make_shared<Entity>(regs);
            _ptr->AddComponent<component::NameComponent>(name);
            return _ptr;
        }

        /**
         * @brief 用entity三方库的能力 添加 删除 或者查找 Component
        */

        inline entt::entity GetEntity() 
        { 
            return m_entity; 
        }

        template <typename T, typename... Args>
        inline T &AddComponent(Args &&...args)
        {
            T &t = m_registry->emplace<T>(m_entity, std::forward<Args>(args)...);
            return t;
        }

        template <typename T, typename... Args>
        inline bool AddComponentAndReturnStatus(Args &&...args)
        {
            if (this->HasComponent<T>())
                return false;
            this->AddComponent<T>(std::forward<Args>(args)...);
            return true;
        }

        template <typename T, typename... Args>
        inline auto AddOrReplaceComponent(Args &&...args)
        {
            T &t = m_registry->emplace_or_replace<T>(m_entity, std::forward<Args>(args)...);
        }

        template <typename T>
        inline T &GetComponent()
        {
            return m_registry->get<T>(m_entity);
        }

        template <typename T, typename... Args>
        inline T &GetOrAddComponent(Args &&...args)
        {
            T &t = m_registry->get_or_emplace<T>(m_entity, std::forward<Args>(args)...);
            return t;
        }

        template <typename T>
        inline T *TryGetComponent()
        {
            return m_registry->try_get<T>(m_entity);
        }

        template <typename T>
        inline auto HasComponent() const -> bool
        {
            return m_registry->any_of<T>(m_entity);
        }

        template <typename T>
        inline auto RemoveComponent()
        {
            return m_registry->remove<T>(m_entity);
        }

        inline auto operator==(const Entity &other) const
        {
            return m_entity == other.m_entity;
        }

        inline auto operator!=(const Entity &other) const
        {
            return !(*this == other);
        }

        inline std::shared_ptr<entt::registry> GetRegistry()
        {
            return m_registry;
        }

        /**
         * @brief 序列化相关
        */

        inline friend void to_json(nlohmann::json &j, const Entity &P)
        {
            j = nlohmann::json::array();
            for (auto &&curr : P.m_registry->storage())
            {
                if (auto &storage = curr.second; storage.contains(P.m_entity))
                {
                    entt::id_type id = curr.first;
                    void *componentTypeAny = storage.get(P.m_entity);
                    auto componentJson = nlohmann::json();
                    componentJson["ComponentType"] = ComponentSerilizationMap::GetName(id);
                    componentJson["ComponentData"] = ComponentSerilizationMap::GetJsonFromVoidType(id, componentTypeAny);
                    j.push_back(componentJson);
                }
            }
        }

        inline friend void to_json(nlohmann::json &j, const Entity::Ptr &P)
        {
            to_json(j, *P);
        }

        inline friend void from_json(const nlohmann::json &j, Entity &P)
        {
            for (auto &componentJson : j)
            {
                auto componentType = componentJson.at("ComponentType").get<std::string>();
                auto ComponentData = componentJson.at("ComponentData");
                auto &func = ComponentSerilizationMap::GetBindFunc(componentType);
                func(P.m_entity, P.m_registry, ComponentData);
            }
        }

        inline friend void from_json(const nlohmann::json &j, Entity::Ptr &P)
        {
            P = std::make_shared<Entity>();
            from_json(j, *P);
        }

    private:
        entt::entity m_entity;
        std::shared_ptr<entt::registry> m_registry;
    };

    class ComponentRegisterationMap
    {
    public:
        using EntityCreateComponentFunc = std::function<bool(Entity::Ptr &)>; // 组件创建函数
        using EntityPreCalcComponentFunc = std::function<void(void *&)>;      // 组件预计算函数

    private:
        inline static std::unordered_map<std::string, EntityCreateComponentFunc> str_to_ctorFunc;
        inline static std::unordered_map<entt::id_type, EntityPreCalcComponentFunc> idtype_to_preCalcFunc;

    public:
        template <typename T>
        inline static void Register(std::string_view name)
        {
            // Register时也注册进各种查找表
            ComponentSerilizationMap::idtype_to_name[entt::type_id<T>().hash()] = name;
            ComponentSerilizationMap::idtype_to_regFunc[entt::type_id<T>().hash()] = &T::FromVoidType;
            ComponentSerilizationMap::str_to_bindFunc[name.data()] = &T::BindComponentFromJson;
            str_to_ctorFunc[name.data()] = &ComponentCtorFunc<T>;
        }

        // 注册预计算函数
        template <typename T>
        inline static void RegisterPreCalculation(EntityPreCalcComponentFunc func)
        {
            idtype_to_preCalcFunc[entt::type_id<T>().hash()] = func;
        }

        // 添加Component并返回是否成功
        template <typename T>
        inline static bool ComponentCtorFunc(Entity::Ptr &entity)
        {
            return entity->AddComponentAndReturnStatus<T>();
        }

        inline static std::unordered_map<std::string, EntityCreateComponentFunc> &GetAllCtorFuncs() { return str_to_ctorFunc; }
        inline static std::unordered_map<entt::id_type, EntityPreCalcComponentFunc> &GetAllPreCalcFuncs() { return idtype_to_preCalcFunc; }
    };
}