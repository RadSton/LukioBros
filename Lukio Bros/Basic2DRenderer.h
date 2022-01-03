#pragma once
#include "RenderContext.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Animation.h"


namespace Renderer {
	class Basic2D {
	public:

		// MVP <- Model(pos(vec3)) * View(comming soon) * Projection(ortho(mat4))
		void Init(const char* vertex, const char* fragment) {
			shader = Engine::Shader(vertex, fragment);
			ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
			view = Math::Vector2f(000, 000);
		}

		void moveCamera(float x, float y) {
			view.add(-x, -y);
		}

		void UpdateSize(float w, float h) {
			ortho = glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
		}

		void RenderShadedMesh(Engine::Mesh* mesh, Engine::Texture* tex, Engine::Shader* shad) {
			tex->Bind(0);
			shad->Bind();
			shad->setVector2f("pos", (mesh->getPosition()));
			shad->setVector2f("view", view);
			shad->setInt("u_tex", 0);
			shad->setMatrix4f("ortho", ortho);
			mesh->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			mesh->Unbind();
			shad->Unbind();
			tex->Unbind();
		}
		void RenderMesh(Engine::Mesh* mesh, Engine::Texture* tex) {
			tex->Bind(0);
			shader.Bind();
			shader.setVector2f("pos", (mesh->getPosition()));
			shader.setVector2f("view", view);
			shader.setInt("u_tex", 0);
			shader.setMatrix4f("ortho", ortho);
			mesh->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			mesh->Unbind();
			shader.Unbind();
			tex->Unbind();
		};
		void RenderMeshWithoutTransforming(Engine::Mesh* mesh, Engine::Texture* tex, Engine::Shader* shad) {
			tex->Bind(0);
			shad->Bind();
			shad->setInt("u_tex", 0);
			mesh->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			mesh->Unbind();
			shad->Unbind();
			tex->Unbind();
		};

		void RenderMesh(Engine::Mesh* mesh, Engine::Texture* tex, int slot) {
			tex->Bind(slot);
			shader.Bind();
			shader.setVector2f("pos", (mesh->getPosition()));
			shader.setVector2f("view", view);
			shader.setInt("u_tex", slot);
			shader.setMatrix4f("ortho", ortho);
			mesh->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			mesh->Unbind();
			shader.Unbind();
			tex->Unbind();
		};
		void applyMVP(Engine::Shader* s)
		{
			s->setMatrix4f("ortho", ortho);
			s->setVector2f("view", view);
		};
	private:
		Engine::Shader shader;
		glm::mat4 ortho;
		Math::Vector2f view;
	};
}