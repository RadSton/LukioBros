#pragma once
#include "RenderContext.h";

namespace Engine {
	class Mesh {
	public:
		Mesh();
		void Load(const GLfloat [],uint32_t, const GLfloat[], const GLuint [], uint32_t);
		void Bind();
		void Unbind();
		void Move(float x, float y);
		Math::Vector2f* getPosition();
		GLuint getTextureBuffer();

	private: 
		GLuint vao; // Vertex Array Object
		GLuint vbo; // Vertex Buffer Object
		GLuint tbo; // Texture Buffer Object
		GLuint ibo; // Ibdecies Buffer Object
		Math::Vector2f position;
	};
}