#pragma once

class Button : public GameObject
{
private:
	Vector2D pos;
	Texture* texture;

public:
	void onClick();
	void onPointerOver();
	void onPointerOut();
};

