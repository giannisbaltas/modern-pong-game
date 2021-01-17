#pragma once

class GameObject
{
public:
	//set them pure virtual
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};