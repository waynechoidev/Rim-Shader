#pragma once

#include <GL\glew.h>
#include "Common.h"
#include <vector>

class Mesh
{
public:
	Mesh();

	void initialise(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
	void render(GLint shape);
	void render();

	~Mesh();

private:
	GLuint _VAO, _VBO, _IBO;
	GLsizei _indexCount;

	void clear();
};

