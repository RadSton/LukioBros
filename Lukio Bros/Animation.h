#pragma once
#include "Core.h"

namespace Engine {
	class Animation {
	public:
		Animation();
		Animation(Engine::Texture*, uint32_t obX, uint32_t obY);
		void nextFrame();
		void addFrame(uint32_t x, uint32_t y);
		void save();
		void setLoop(bool);
		bool getLoop();
		uint32_t getCurrentFrame();
		uint32_t getLastFrame();
	private:
		uint32_t textureWidth,textureHeight;
		Engine::Texture* texture;
		bool looped;
		std::unordered_map<uint32_t, Math::Vector2f> frames;
		uint32_t currentFrame, lastFrame;
	};
}