#pragma once

#include <string>
#include <vector>
#include <memory>

namespace rtype::engine {

class Scene;
class Entity;

class BackgroundManager {
public:
    BackgroundManager(Scene& scene, float windowWidth, float windowHeight);

    void addScrollingBackground(const std::string& imagePath, float scrollSpeed);
    void update();

private:
    Scene& scene;
    float windowWidth;
    float windowHeight;
    
    struct BackgroundLayer {
        Entity* entity1;
        Entity* entity2;
        float scrollSpeed;
        float imageWidth;
        float scale;
    };
    
    std::vector<BackgroundLayer> layers;
};

}