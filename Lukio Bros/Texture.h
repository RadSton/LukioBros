#pragma once
#include "RenderContext.h"

namespace Engine {
	class Texture {
	public:
		Texture();
		Texture(const char*);
		void Bind(int s = 0);
		void Unbind(int s = 0);
		Math::Vector2f* getSize();
	private:
		GLuint textureID;
		int32_t width, height, bpp;
		Math::Vector2f size;
		unsigned char* localBuffer;
	};
}