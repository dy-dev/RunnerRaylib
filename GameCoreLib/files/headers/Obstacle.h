#pragma once
#include "GraphicElement.h"


enum class EObstacleState
{
	ON,
	OFFSCREEN,
	COLLIDED
};

class Obstacle :
	public GraphicElement
{
private:
	bool m_bIsOffScreen;
	EObstacleState m_eState;

public:
	Obstacle(const std::string& p_TexturePath, float p_Speed);
	virtual void update() override;
	virtual void draw() override;
	bool isOffScreen();
	EObstacleState getState();
	void setState(EObstacleState p_bCounted);
};

