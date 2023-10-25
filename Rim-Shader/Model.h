#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();

	void load(const std::string& fileName);
	void render();
	void renderNormal();

	~Model(){}

private:

	void loadNode(aiNode* node, const aiScene* scene);
	void loadMesh(aiMesh* mesh, const aiScene* scene);
	void loadMaterials(const aiScene* scene);

	std::vector<std::shared_ptr<Mesh>> meshList;
	std::vector<std::shared_ptr<Mesh>> normalList;
	std::vector<std::shared_ptr<Texture>> textureList;
	std::vector<unsigned int> meshToTex;
};