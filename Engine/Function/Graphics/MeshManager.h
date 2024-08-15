#pragma once
#include "Engine/Core/Singleton.hpp"
#include "Engine/Core/SubSystem.hpp"


namespace AnneEngine
{
    class MeshManager final : public Singleton<MeshManager>
    {
    private:
        // std::unordered_map<std::string, std::vector<Mesh::Ptr>> m_meshLists;
        // std::unordered_map<std::string, std::array<float, 6>> m_meshListBoxs;

    public:
        MeshManager() = delete;
        MeshManager(token){};
        ~MeshManager();

        size_t GetMeshsCount(std::string_view name);
        void DeleteMeshList(std::string name);
        std::vector<std::string> GetAllMeshListName();
        bool Import(std::string_view obj_path);

    public:
        inline std::array<std::string, 2> GetBuildInMeshsName() const { return {"Cube", "Sphere"}; };
    };
}