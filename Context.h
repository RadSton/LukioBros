#pragma once
#include "Core.h";

namespace Luka {
	class Context {
	public:
		static void Init();
		static void Render();
		static void Update(float, GLFWwindow*);
		static void Close();
	};
}