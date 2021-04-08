#pragma once
#include "Scene.h"
class StartMenu :
    public Scene
{
public:
    StartMenu(std::string name);
    void InitScene(float windowWidth, float windowHeight) override;
    void Update() override;
    void KeyboardDown() override;
    void Separate(b2Vec2 newPair, int type) override;
};

