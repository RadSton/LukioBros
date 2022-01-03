#pragma once
#include "Core.h";


namespace Luka {
	class Context {
	public:
		static void Init();
		static void WindowUpdate(int, int);
		static void Render();
		static void ImGuiRender(float timing[]);
		static void OnEvent(std::string);
		static void Update(float, GLFWwindow*);
		static void Close();
	};
}