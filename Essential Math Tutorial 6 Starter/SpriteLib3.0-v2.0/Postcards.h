#pragma once
#include "Scene.h"
#include "PhysicsPlayground.h"

class Postcards : public Scene
{
public:
	Postcards(std::string name);
	void InitScene(float windowWidth, float windowHeight) override;
	void BuildPostcards();
	
	void Update();


	void Separate(b2Vec2 newPair, int type = 0) override;

protected:
	PhysicsPlaygroundListener listener;
	int nextScene = 0;
	int postcardMin = 0;
	int postcardMax = 0;
	int uiElements[2];

	//Sound library
private: 
	ToneFire::CoreSound transitionBGM{ "transitionBGM.wav", false, true, true };
};

