#include "tangram/engine/rendering/graphics_api.hpp"
#include "tangram/engine/rendering/vertex_layout.hpp"

#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <tangram/engine/rendering/model.hpp>
#include <vector>

namespace tangram::engine
{
    static void processMesh(const aiMesh* mesh, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals,
                            std::vector<uint32_t>& indices, std::vector<glm::vec2>& texCoords,
                            std::vector<glm::vec3>& tangents, std::vector<int> texIndices)
    {
        int texIndex = std::max(static_cast<int>(mesh->mMaterialIndex) - 1, 0);
        for (uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            const aiVector3D& pos = mesh->mVertices[i];
            positions.push_back({pos.x, pos.y, pos.z});
            const aiVector3D& norms = mesh->mNormals[i];
            if (mesh->HasNormals())
            {
                normals.push_back(glm::vec3{norms.x, norms.y, norms.z});
            }
            if (mesh->HasTextureCoords(0))
            {
                const aiVector3D& aiTexcoord = mesh->mTextureCoords[0][i];
                texCoords.push_back(glm::vec2{aiTexcoord.x, aiTexcoord.y});
                texIndices.push_back(texIndex);
            }
            if (mesh->HasTangentsAndBitangents())
            {
                const aiVector3D& aiTangent = mesh->mTangents[i];
                tangents.push_back(glm::vec3(aiTangent.x, aiTangent.y, aiTangent.z));
            }
        }
        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace& face = mesh->mFaces[i];
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }
    }

    Model::Model(const std::unique_ptr<GraphicsAPI>& graphics, const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                                                                   aiProcess_CalcTangentSpace);
        if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
        {
            std::cerr << "Failed to load model: " << path << std::endl;
            std::exit(EXIT_FAILURE);
        }
        mMeshes.resize(scene->mNumMeshes);
        uint32_t baseVertex = 0;
        uint32_t baseIndex = 0;
        for (uint32_t i = 0; i < mMeshes.size(); i++)
        {
            mMeshes[i].indexCount = scene->mMeshes[i]->mNumFaces * 3;
            mMeshes[i].baseVertex = baseVertex;
            mMeshes[i].baseIndex = baseIndex;

            baseVertex += scene->mMeshes[i]->mNumVertices;
            baseIndex += mMeshes[i].indexCount;
        }
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<uint32_t> indices;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> tangents;
        std::vector<int> texIndices;
        std::cout << "Loading model: " << path << std::endl;
        for (uint32_t i = 0; i < mMeshes.size(); i++)
        {
            processMesh(scene->mMeshes[i], positions, normals, indices, texCoords, tangents, texIndices);
        }
        std::shared_ptr<VertexBuffer> pBuffer =
            graphics->createVertexBuffer(positions.size() * sizeof(positions[0]), positions.data());
        std::shared_ptr<VertexBuffer> nBuffer =
            graphics->createVertexBuffer(normals.size() * sizeof(normals[0]), normals.data());
        std::shared_ptr<VertexBuffer> tBuffer =
            graphics->createVertexBuffer(texCoords.size() * sizeof(texCoords[0]), texCoords.data());
        std::shared_ptr<VertexBuffer> tanBuffer =
            graphics->createVertexBuffer(tangents.size() * sizeof(tangents[0]), tangents.data());
        std::shared_ptr<VertexBuffer> tiBuffer =
            graphics->createVertexBuffer(texIndices.size() * sizeof(texIndices[0]), texIndices.data());
        VertexLayout pnLayout{};
        pnLayout.push<float>(3);
        VertexLayout tLayout{};
        tLayout.push<float>(2);
        VertexLayout tiLayout{};
        tiLayout.push<int>(1);
        std::shared_ptr<IndexBuffer> iBuffer = graphics->createIndexBuffer(indices.size(), indices.data());
        VertexArrayDescription desc{
            .vertexBufers = {pBuffer, nBuffer, tBuffer, tanBuffer, tiBuffer},
            .layouts = {pnLayout, pnLayout, tLayout, pnLayout, tiLayout},
            .indexBuffer = iBuffer,
        };
        mVertexArray = graphics->createVertexArray(desc);
    }

    void Model::draw(const std::unique_ptr<GraphicsAPI>& graphics) const
    {
        graphics->bindVertexArray(mVertexArray);
        for (const Mesh& mesh : mMeshes)
        {
            graphics->drawElementsBaseVertex(
                mesh.indexCount, reinterpret_cast<void*>(sizeof(uint32_t) * mesh.baseIndex), mesh.baseVertex);
        }
    }
} // namespace tangram::engine
