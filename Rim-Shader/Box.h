#pragma once

#include "Mesh.h"
#include "Common.h"
#include <memory>

class Box
{
public:
	Box();
	void initialise();
	
	void draw();
	void drawNormal();

	~Box(){}

private:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Mesh> _normal;

	std::vector<Vertex> _meshVertices;
	std::vector<GLuint> _meshIndices;

	std::vector<Vertex> _normalVertices;
	std::vector<GLuint> _normalIndices;
};

