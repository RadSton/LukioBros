#pragma once
#include "Core.h"

namespace Engine {
	class Input {
	public:
		static bool isPressed(int, GLFWwindow*);
		static bool isMousePressed(int, GLFWwindow*);
		static Math::Vector2f mouseLocation(GLFWwindow*);		
	};
}