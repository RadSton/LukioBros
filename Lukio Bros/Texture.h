#pragma once
#include "Core.h"

namespace Engine {
	class Texture {
	public:
		Texture();
		Texture(const char*);
		void Bind(int s = 0);
		void Unbind(int s = 0);
	private:
		GLuint textureID;
		int32_t width, height, bpp;
		unsigned char* localBuffer;
	};
}