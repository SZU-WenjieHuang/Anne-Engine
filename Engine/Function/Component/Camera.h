#pragma once
#include "Engine/Core/Singleton.hpp"

namespace AnneEngine
{
    namespace component
    {
        class Camera
        {
        public:
            enum class Action
            {
                Forward,
                Backward,
                Left,
                Right,
                Up,
                Down,
            };

            using Ptr = std::shared_ptr<Camera>;
            Camera(glm::vec3 positon = glm::vec3(0, 1.5f, 3.f), glm::vec3 lookat = glm::vec3(0, 0, -1.f),
                   float near = 0.1, float far = 150, float fov = 90.0,
                   float sensitivity = 0.001f, float speed = 0.1f, float max_pitch_rate = 5.f, float max_heading_rate = 5.f);
        };
    }
}