#pragma once
#include "Engine/Function/SceneManager.h"
using namespace AnneEngine;


Scene::Ptr SceneManager::GetCurrentScene()
{
    return m_current_scene;
}
Scene::Node::Ptr &SceneManager::GetCurrentSceneNode()
{
    return m_current_scene->GetRootNode();
}