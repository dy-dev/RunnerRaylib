#pragma once
#include "GraphicElement.h"

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

public:
	Player(const std::string& p_Texture, float p_Speed, int p_iNbColumns, int p_iNbLines);
	virtual void update() override;
	virtual void draw() override;

	void manageInput();
};

