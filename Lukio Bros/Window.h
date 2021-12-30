#pragma once
#include "Core.h"

namespace Engine {

	class Window {
	public:
		Window();
		void Init();
		void Destroy();
	private:
		
		GLFWwindow* window;
		uint32_t statusCode;
	
	};

}