#include <raymath.h>
#include "Rock.h"
#include "GameManager.h"

Rock::Rock(const std::string& p_TexturePath, float p_Speed)
	: Obstacle(p_TexturePath, p_Speed)
	, m_fCoeffResize{ 0.1f }
{
}


void Rock::update()
{
	m_Position = Vector2Subtract(m_Position, Vector2{ (float)GameManager::getInstance()->getGameSpeed(), 0 });
}

void Rock::draw()
{
	DrawTextureEx(m_Texture, m_Position, 0, m_fCoeffResize, RAYWHITE);
}

void Rock::setPosition(const Vector2& p_NewPosition)
{
	GraphicElement::setPosition(p_NewPosition);
	m_Position = Vector2Subtract(m_Position, { 0,m_Texture.height * m_fCoeffResize });
}