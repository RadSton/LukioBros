#pragma once
#include "Core.h"

namespace Luka {
	struct Intro {
		Engine::Animation anim; 
		Engine::Texture tx;
		Engine::Mesh mesh;
		Engine::Shader introShader;

		unsigned int animCount;
		float timer;

		void Init() {
			tx = Engine::Texture("assets/textures/intro/rad.png");
			anim = Engine::Animation(&tx, 900);

			introShader = Engine::Shader("assets/shaders/center/vertex.glsl", "assets/shaders/center/fragment.glsl");
			for(int i = 0; i < 15; i++) anim.addFrame(Math::Vector2f(i,1));
			for (int i = 0; i < 15; i++) anim.addFrame(Math::Vector2f(i, 0));
			mesh.CreateSquare(0.5f);
		}
		 void Render(Renderer::Basic2D* basic2d, Renderer::Batch2D* batch2d) {
			 if (animCount == 41) return;
			basic2d->RenderMeshWithoutTransforming(&mesh, &tx, &introShader);
		}

		 
		 void Update(float delta, GLFWwindow* window) {
			 timer += delta;
			 if (timer > 0.1f) {
				if(animCount < 28) anim.nextFrame(&mesh);
				timer -= 0.1f; 
				if (animCount == 40) {
					Luka::Context::OnEvent("finshedIntro");
					Close();
				}
				animCount++;
			 }
		}
		 void Close() {
			 if (animCount == 41)return;
			 animCount = 41;
			 timer = 0.0f;
			 tx.Delete();
			 introShader.Close();
			 mesh.Delete();
		}
		 void ImGuiRender() {}
		 void ImGuiDebugRender() { 
			 ImGui::Text("2D Overlayfile: Intro.h"); 
			 ImGui::Text("Intro-Animation Count: %i", animCount);
			 ImGui::Text("Intro-Animation Timer: %.3f", timer);
		 }
	};
}