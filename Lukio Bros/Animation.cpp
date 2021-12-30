#include "Animation.h"

using namespace Engine;

Animation::Animation() {}

Animation::Animation(Engine::Texture* tex, uint32_t w, uint32_t h) 
	: textureWidth(w), textureHeight(h), texture(tex), looped(true), 
	currentFrame(0), lastFrame(0) 
{}

void Animation::nextFrame() {

}

void Animation::addFrame(uint32_t x, uint32_t y) {

}

void Animation::nextFrame() {

}
