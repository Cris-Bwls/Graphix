#include "Mesh.h"
#include "gl_core_4_4.h"


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::InitialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);

	// Generate Buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// Bind vert array
	glBindVertexArray(vao);

	// Bind vert buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	Vertex verts[6];
	verts[0].position = { -0.5f, 0, 0.5f, 1 };
	verts[1].position = { 0.5f, 0, 0.5f, 1 };
	verts[2].position = { -0.5f, 0, -0.5f, 1 };

	verts[3].position = { -0.5f, 0, -0.5f, 1 };
	verts[4].position = { 0.5f, 0, 0.5f, 1 };
	verts[5].position = { 0.5f, 0, -0.5f, 1 };

	// Fill vert buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), verts, GL_STATIC_DRAW);

	// enable first element as pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	verts[0].normal = { 0,1,0,0 };
	verts[1].normal = { 0,1,0,0 };
	verts[2].normal = { 0,1,0,0 };
	verts[3].normal = { 0,1,0,0 };
	verts[4].normal = { 0,1,0,0 };
	verts[5].normal = { 0,1,0,0 };

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	verts[0].texCoord = { 0, 1 }; // bottom left
	verts[1].texCoord = { 1, 1 }; // bottom right
	verts[2].texCoord = { 0, 0 }; // top left
	verts[3].texCoord = { 0, 0 }; // top left
	verts[4].texCoord = { 1, 1 }; // bottom right
	verts[5].texCoord = { 1, 0 }; // top right

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Quad has 2 tri's
	triCount = 2;
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	// using indices or just verts?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}
