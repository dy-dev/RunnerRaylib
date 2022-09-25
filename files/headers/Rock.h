#pragma once
#include "Obstacle.h"
class Rock :
	public Obstacle
{
private:
	float m_fCoeffResize;

public:
	Rock(const std::string& p_TexturePath, float p_Speed);

	virtual void update() override;
	virtual void draw() override;
	virtual void setPosition(const Vector2& p_NewPosition) override;

};
