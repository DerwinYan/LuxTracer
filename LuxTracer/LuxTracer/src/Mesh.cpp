
#include <Mesh.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <Logger.h>

#pragma warning(push)
#pragma warning( disable : 6011 )

namespace lux
{
	Mesh::Mesh(std::string_view const& filePath)
	{
		Assimp::Importer importer;

		unsigned importFlags
		{
			aiProcess_Triangulate |   // Make sure we get triangles rather than nvert polygons
			aiProcess_FindInstances |   // search for instanced meshes and remove them by references to one master
			aiProcess_JoinIdenticalVertices |   // join identical vertices/ optimize indexing
			aiProcess_RemoveRedundantMaterials |   // remove redundant materials
			aiProcess_FindInvalidData |    // detect invalid model data, such as invalid normal vectors
			aiProcess_PreTransformVertices |
			aiProcess_RemoveComponent |
			aiProcess_GenSmoothNormals |
			aiProcess_FixInfacingNormals
		};
		importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);
		importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
			aiComponent_MATERIALS | aiComponent_COLORS | aiComponent_TEXCOORDS |
			aiComponent_BONEWEIGHTS | aiComponent_ANIMATIONS | aiComponent_TEXTURES |
			aiComponent_LIGHTS | aiComponent_CAMERAS);
		aiScene const* scene{ importer.ReadFile(filePath.data(), importFlags)};
		aiMesh* pMesh{};

		LogAssert(scene, "Unable to read model!");
		pMesh = scene->mMeshes[scene->mRootNode->mMeshes[0]];
		LogAssert(pMesh, "Unable to read mesh!");

		//Read vertices data
		for (unsigned i{}; i < pMesh->mNumFaces; ++i)
		{
			Triangle tri;
			for (int ii{}; ii < 3; ++ii)
			{
				auto const& vert = pMesh->mVertices[pMesh->mFaces[ii].mIndices[ii]];
				tri.vertices[ii].pos = glm::vec3{ vert.x, vert.y, vert.z };
				auto const& norm = pMesh->mNormals[pMesh->mFaces[ii].mIndices[ii]];
				tri.vertices[ii].normal = glm::vec3{ norm.x, norm.y, norm.z };
				auto const& uv = pMesh->mTextureCoords[pMesh->mFaces[ii].mIndices[ii]];
				tri.vertices[ii].uv = glm::vec2{ uv->x, uv->y };
			}
			triangles.emplace_back(std::move(tri));
		}
	}
}

#pragma warning( pop )
