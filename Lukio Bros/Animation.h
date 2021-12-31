#pragma once
#include "Core.h"

namespace Engine {
	class Animation {
	public:
		Animation();
		Animation(Engine::Texture*);
		Animation(Engine::Texture*, uint32_t);
		void nextFrame(Engine::Mesh*);
		void addFrame(Math::Vector2f);
		void playFrame(Math::Vector2f*, Engine::Mesh*);
		uint32_t getCurrentFrame();
		uint32_t getLastFrame();
	private:
		Engine::Texture* texture;
		std::unordered_map<uint32_t, Math::Vector2f> frames;
		uint32_t currentFrame, lastFrame, tileSize;
	};
}