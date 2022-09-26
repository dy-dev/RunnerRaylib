#pragma once
#include "GraphicElement.h"

class Obstacle;
class Player :
    public GraphicElement
{
protected:
	bool m_bIsJumping;
	Rectangle m_FrameRec;
	int m_iFrameCounter;
	int m_iCurrentFrame;
	int m_iNbSpritsByLine;
	int m_iNbLines;
	int m_iScore;

public:
	Player(const std::string& p_Texture, float p_Speed, int p_iNbColumns, int p_iNbLines);
	virtual void update() override;
	virtual void draw() override;
	float getHeight();
	void manageInput();
	int getScore() const;
	bool isColliding(Obstacle* p_pObstacle);
	void addPoints(int p_iPoints);
};

