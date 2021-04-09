#pragma once
#include "Scene.h"
class EndScreen :
    public Scene
{
public:
    EndScreen(std::string name);
    void InitScene(float windowWidth, float windowHeight) override;
    void Update() override;
    void KeyboardDown() override;
    void Separate(b2Vec2 newPair, int type) override;

protected:
    //MENU SCREENS\\
    //0 = End game image
    //1 = Final message display
    //2 = Credits
    //3 = Thanks for playing screen
    int endScreens[4]; 

private:
    ToneFire::CoreSound menuBGM{ "menuBGM.wav", false, true, true };
};

