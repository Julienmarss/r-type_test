#include "engine/graphics/Animation.hpp"

Animation::Animation() 
    : frameCount(0), currentFrame(0), frameTime(0.15f), 
      elapsedTime(0.f), loop(true) {
}

void Animation::addFrame(int x, int y, int width, int height) {
    frames.push_back({x, y, width, height});
    frameCount = static_cast<int>(frames.size());
}

void Animation::setFrameTime(float time) {
    frameTime = time;
}

void Animation::setLoop(bool loopValue) {
    loop = loopValue;
}

const AnimationFrame* Animation::getCurrentFrame() const {
    if (currentFrame < frameCount && currentFrame >= 0) {
        return &frames[currentFrame];
    }
    return nullptr;
}

int Animation::getCurrentFrameIndex() const {
    return currentFrame;
}