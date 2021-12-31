#include "Mesh.h"
/*
Private Var
GLuint vao;  Vertex Array Object
GLuint vbo; Vertex Buffer Object
		
*/

Engine::Mesh::Mesh(){}

void Engine::Mesh::Load(const GLfloat vertecies[], uint32_t verteciesLe, const GLfloat txCoordinates[], const GLuint inceies[], uint32_t indeciesLe) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)0);
	glBufferData(GL_ARRAY_BUFFER, verteciesLe * sizeof(float), vertecies, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);


	glDisableVertexAttribArray(0);


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), txCoordinates, GL_DYNAMIC_DRAW);

	
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeciesLe * sizeof(inceies[0]), inceies, GL_STATIC_DRAW);


	glBindVertexArray(0);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1); // WEIL DIE FAULHEIT SIEGT
	// and is saved 4 calls per render xD idk why this works
	
}

void Engine::Mesh::Bind() {
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Engine::Mesh::Unbind() {
	glBindVertexArray(0);
}

void Engine::Mesh::Move(float x, float y) {
	position.add(x, y);
}

Math::Vector2f* Engine::Mesh::getPosition() {
	return &position;
}

GLuint Engine::Mesh::getTextureBuffer() {
	return tbo;
}