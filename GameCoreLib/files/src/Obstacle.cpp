#include "Obstacle.h"

Obstacle::Obstacle(const std::string& p_TexturePath, float p_Speed)
	: GraphicElement(p_TexturePath, p_Speed)
	, m_bIsOffScreen{ false }
	, m_eState{ EObstacleState::ON }
{
}

void Obstacle::update()
{
	if (m_Position.x + m_fWidth < 0)
	{
		m_bIsOffScreen = true;
	}
}

void Obstacle::draw()
{
}


bool Obstacle::isOffScreen()
{
	return m_bIsOffScreen;
}

EObstacleState Obstacle::getState()
{
	return m_eState;
}

void Obstacle::setState(EObstacleState p_bCounted)
{
	m_eState = p_bCounted;
}



