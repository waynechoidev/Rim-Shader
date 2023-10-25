#include "Model.h"

Model::Model()
{
}

void Model::render()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textureList.size() && textureList[materialIndex])
		{
			textureList[materialIndex]->use();
		}

		meshList[i]->render();
	}
}

void Model::renderNormal()
{
	for (size_t i = 0; i < normalList.size(); i++)
	{
		normalList[i]->render(GL_LINES);
	}
}

void Model::load(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		std::cout << "Model failed to load" << "\n";
		return;
	}

	loadNode(scene->mRootNode, scene);

	loadMaterials(scene);
}

void Model::loadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		loadNode(node->mChildren[i], scene);
	}
}

void Model::loadMesh(aiMesh* mesh, const aiScene* scene)
{
	const GLfloat scale = 0.08f;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Vertex> normalVertices;
	std::vector<GLuint> normalIndices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		v.position = {mesh->mVertices[i].x * scale, mesh->mVertices[i].y * scale, mesh->mVertices[i].z * scale };
		if (mesh->mTextureCoords[0])
		{
			v.texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		v.normal = glm::normalize(glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
		vertices.push_back(v);

		Vertex n;
		n.position = { mesh->mVertices[i].x * scale, mesh->mVertices[i].y * scale, mesh->mVertices[i].z * scale };
		n.normal = glm::normalize(glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
		n.texcoord.x = n.texcoord.y = 0.0f;
		normalVertices.push_back(n);

		n.texcoord.x = 1.0f;
		normalVertices.push_back(n);

		normalIndices.push_back(GLuint(2 * i));
		normalIndices.push_back(GLuint(2 * i + 1));

	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	auto newMesh = std::make_shared<Mesh>();
	newMesh->initialise(vertices, indices);
	meshList.push_back(newMesh);

	auto newNormal = std::make_shared<Mesh>();
	newNormal->initialise(normalVertices, normalIndices);
	normalList.push_back(newNormal);

	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene* scene)
{
	textureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				textureList[i] = std::make_shared<Texture>();

				textureList[i]->initialise(texPath.c_str());
			}
		}
	}
}
