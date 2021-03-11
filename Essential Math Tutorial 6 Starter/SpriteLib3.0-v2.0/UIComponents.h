#pragma once
class UIComponents
{
public:
	void UpdateUI(int entity);
	void SetWindowSize(float width, float height) {wWidth = width; wHeight = height;};

private:
	float wWidth = 0;
	float wHeight = 0;
};

