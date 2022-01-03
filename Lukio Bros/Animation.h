#pragma once

namespace Engine {
	class Animation {
	public:
		Animation() {}
		Animation(Engine::Texture* tex)
			: texture(tex), currentFrame(0), lastFrame(0), tileSize(128)
		{}
		Animation(Engine::Texture* tex, uint32_t tile)
			: texture(tex), currentFrame(0), lastFrame(0), tileSize(tile)
		{}
		void nextFrame(Engine::Mesh* mesh) {
			if (frames.empty()) return;
			if ((currentFrame + 1) >= lastFrame) currentFrame = 0;
			else currentFrame++;

			Math::Vector2f* frame = &frames[currentFrame];

			if ((currentFrame - 1) >= 0) {
				if (frame->getX() == frames[currentFrame - 1].getX() && frame->getY() == frames[currentFrame - 1].getY()) {
					return;
				}
			}

			Math::Vector2f* texSize = texture->getSize();

			GLfloat txCoords[]{
				(frame->getX() * tileSize) / texSize->getX()	 ,(frame->getY() * tileSize) / texSize->getY() ,
				((frame->getX() + 1) * tileSize) / texSize->getX() ,(frame->getY() * tileSize) / texSize->getY() ,
				((frame->getX() + 1) * tileSize) / texSize->getX() ,((frame->getY() + 1) * tileSize) / texSize->getY() ,
				(frame->getX() * tileSize) / texSize->getX()	 ,((frame->getY() + 1) * tileSize) / texSize->getY()
			};
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getTextureBuffer());
			glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), &txCoords);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		void addFrame(Math::Vector2f vec) {
			frames[lastFrame] = vec;
			lastFrame++;
		}
		void playFrame(Math::Vector2f* frame, Engine::Mesh* mesh) {
			Math::Vector2f* texSize = texture->getSize();

			GLfloat txCoords[]{
				(frame->getX() * tileSize) / texSize->getX()	 ,(frame->getY() * tileSize) / texSize->getY() ,
				((frame->getX() + 1) * tileSize) / texSize->getX() ,(frame->getY() * tileSize) / texSize->getY() ,
				((frame->getX() + 1) * tileSize) / texSize->getX() ,((frame->getY() + 1) * tileSize) / texSize->getY() ,
				(frame->getX() * tileSize) / texSize->getX()	 ,((frame->getY() + 1) * tileSize) / texSize->getY()
			};
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getTextureBuffer());
			glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), &txCoords);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
		uint32_t getCurrentFrame() {
			return currentFrame;
		}
		uint32_t getLastFrame() {
			return lastFrame;
		}

	private:
		Engine::Texture* texture;
		std::unordered_map<uint32_t, Math::Vector2f> frames;
		uint32_t currentFrame, lastFrame, tileSize;
	};
}