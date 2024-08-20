#pragma once
#include "Engine/Function/Scene.h"

namespace AnneEngine
{
    /**
     * @brief 场景管理器(recommended)
     */
    class SceneManager : public Singleton<SceneManager>
    {
    public:
        SceneManager() = delete;
        SceneManager(token) {}
        Scene::Ptr GetCurrentScene();
        Scene::Node::Ptr &GetCurrentSceneNode();

    public:

    private:
        std::unordered_map<Scene::Index, Scene::Ptr> m_scenes;
        Scene::Index m_current_count{0};
        Scene::Ptr m_current_scene{nullptr};
    };
}