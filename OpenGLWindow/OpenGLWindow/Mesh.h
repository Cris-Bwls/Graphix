#pragma once
#include <glm/ext.hpp>

class Mesh
{
public:
	inline Mesh() : triCount(0), vao(0), ibo(0) {};
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void InitialiseQuad();

	virtual void Draw();

protected:

	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

