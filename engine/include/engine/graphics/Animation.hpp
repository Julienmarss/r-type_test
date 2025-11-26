#pragma once
#include "engine/core/Component.hpp"
#include <vector>

struct AnimationFrame {
    int x;
    int y;
    int width;
    int height;
};

class Animation : public Component {
public:
    Animation();
    
    void addFrame(int x, int y, int width, int height);
    void setFrameTime(float time);
    void setLoop(bool loop);
    
    const AnimationFrame* getCurrentFrame() const;
    int getCurrentFrameIndex() const;
    
    int frameCount;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    bool loop;
    
    std::vector<AnimationFrame> frames;
};