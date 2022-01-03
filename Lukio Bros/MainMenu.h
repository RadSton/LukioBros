#pragma once
#include "Core.h"

namespace Luka {
	struct MainMenu {
		static void Init() {

		}
		static void Render(Renderer::Basic2D* basic2d, Renderer::Batch2D* batch2d) {

		}
		static void Update(float delta, GLFWwindow* window) {

		}
		static void Close() {

		}
		static void ImGuiRender() {

		}
		static void ImGuiDebugRender() {
			ImGui::Text("2D Overlayfile: MainMenu.h");
		}
	};
}