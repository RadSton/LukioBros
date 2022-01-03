#pragma once
#include "Basic2DRenderer.h"


static const uint32_t MAX_CUBES = 15000;
static const uint32_t MAX_VERTECIES = MAX_CUBES * 4;
static const uint32_t MAX_INDECIES = MAX_CUBES * 6;


namespace Renderer {
	class Batch2D {
		struct Vertex {
			glm::vec2 pos;
			glm::vec2 textureCoords;
		};

		struct Stats
		{
			unsigned int cubes;
			unsigned int vertecies;
			unsigned int renderCalls = 1;
		};


	public:

		void Init() {
			buffer = new Vertex[MAX_VERTECIES];
			bufferPtr = buffer;
		}

		void CleanUp() {
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteBuffers(1, &indexBuffer);
			glDeleteVertexArrays(1, &vertexArray);

			delete[] buffer;
			
		}
		
		void Begin(Engine::Texture* newTex, const char* shaderVertex, const char* shaderFragment) {
			tex = newTex;
			bufferPtr = buffer;
			shader = Engine::Shader(shaderVertex, shaderFragment);
		}

		void End() {
			glCreateVertexArrays(1, &vertexArray);
			glBindVertexArray(vertexArray);

			glCreateBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, indexBufferCount * sizeof(Vertex) ,buffer, GL_STATIC_DRAW);

			glEnableVertexArrayAttrib(vertexArray, 0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos));


			glEnableVertexArrayAttrib(vertexArray, 1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, textureCoords));


			uint32_t indecies[MAX_INDECIES];
			uint32_t offset = 0;
			for (int i = 0; i < MAX_INDECIES; i += 6) {
				indecies[i + 0] = 0 + offset;
				indecies[i + 1] = 1 + offset;
				indecies[i + 2] = 2 + offset;
				indecies[i + 3] = 2 + offset;
				indecies[i + 4] = 3 + offset;
				indecies[i + 5] = 0 + offset;
				offset += 4;
			}

			glCreateBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDECIES, indecies, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}

		void Render(Renderer::Basic2D* basic2d) {
			shader.Bind();
			tex->Bind(0);
			basic2d->applyMVP(&shader);
			shader.setInt("u_tex", 0);
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, indexBufferCount, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
			tex->Unbind();
			shader.Unbind();
		}

		void Reset() {
			CleanUp();
			Init();
		}

		void DrawQuad(Math::Vector2f pos, int size, Math::Vector2f txCoordsBegin, float txSize) {
#if 0
			const GLfloat vertex[] = {	pos.m_x + -size,  pos.m_y + -size,
										pos.m_x +  size,  pos.m_y + -size,
										pos.m_x +  size,  pos.m_y + size,
										pos.m_x + -size,  pos.m_y + size };

			const GLfloat tx[] = {
				txCoordsBegin.m_x		   , txCoordsBegin.m_y			,
				txCoordsBegin.m_x + txSize, txCoordsBegin.m_y			,
				txCoordsBegin.m_x + txSize, txCoordsBegin.m_y + txSize,
				txCoordsBegin.m_x		   , txCoordsBegin.m_y + txSize
			};

#endif
			bufferPtr->pos			 = { pos.m_x, pos.m_y };
			bufferPtr->textureCoords = { txCoordsBegin.m_x, txCoordsBegin.m_y };
			bufferPtr++;

			bufferPtr->pos			 = {pos.m_x + size, pos.m_y };
			bufferPtr->textureCoords = {txCoordsBegin.m_x + txSize, txCoordsBegin.m_y};
			bufferPtr++;

			bufferPtr->pos			 = {pos.m_x + size, pos.m_y + size};
			bufferPtr->textureCoords = {txCoordsBegin.m_x + txSize, txCoordsBegin.m_y + txSize};
			bufferPtr++;

			bufferPtr->pos			 = {pos.m_x, pos.m_y + size};
			bufferPtr->textureCoords = {txCoordsBegin.m_x, txCoordsBegin.m_y + txSize};
			bufferPtr++;

			indexBufferCount += 6;
			stats.cubes += 1;
			stats.vertecies += 4;
		}

		Stats getStats() {
			return stats;
		}

	private:
		GLuint vertexArray, vertexBuffer, indexBuffer;
		unsigned int indexBufferCount;
		Engine::Texture* tex;
		Engine::Shader shader;
		Vertex* buffer = nullptr, * bufferPtr = nullptr;
		Stats stats;
	};
}