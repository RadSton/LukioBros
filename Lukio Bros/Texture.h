#pragma once
#include "RenderContext.h"

#include "stb_image/stb_image.h"
namespace Engine {
	class Texture {
	public:
		Texture() {};
		Texture(const char* path) : width(0), height(0), bpp(0) {
			stbi_set_flip_vertically_on_load(1);
			localBuffer = stbi_load(path, &width, &height, &bpp, 4);

			size = Math::Vector2f(width, height);

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		void Bind(int slot = 0) {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, textureID);
		};

		void Unbind(int slot = 0) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		Math::Vector2f* getSize() {
			return &size;
		}
	private:
		GLuint textureID;
		int32_t width, height, bpp;
		Math::Vector2f size;
		unsigned char* localBuffer;
	};
}