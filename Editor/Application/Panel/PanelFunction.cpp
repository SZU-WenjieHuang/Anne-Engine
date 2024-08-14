#include "Application/Panel/PanelFunction.h"
#include "Application/FontAwesome/IconsFont.h"
#include "Engine/AnneEngine.h"

using namespace AnneEngine::Application;

// 构造函数 初始化两个Icon
FunctionPanel::FunctionPanel(const std::string &name, bool show) 
: m_name(name)
, m_show(show)
{
    inspection::ModelPreview::Init();
    m_resource_icons["ModelFileImage"] = std::make_shared<Texture2D>("Images/model_icon.png");
    m_resource_icons["ModelAddImage"] = std::make_shared<Texture2D>("Images/model_add_icon.png");
}