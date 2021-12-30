#pragma once
#include "Core.h"

namespace Engine {
	struct Mesh {
	public:
		void Load(const GLfloat [],uint32_t, const GLuint [], uint32_t);
		void Bind();
		void Unbind();
	private: 
		GLuint vao; // Vertex Array Object
		GLuint vbo; // Vertex Buffer Object
		GLuint tbo; // Texture Buffer Object
		GLuint ibo; // Ibdecies Buffer Object
	};
}