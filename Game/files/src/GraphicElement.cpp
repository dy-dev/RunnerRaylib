#include "raymath.h"

#include "GraphicElement.h"

GraphicElement::GraphicElement(const std::string& p_sTexturePath, float p_Speed)
	:GraphicElement(p_sTexturePath, { 0,0 }, p_Speed)
{
	
}

GraphicElement::GraphicElement(const std::string& p_sTexturePath, const Vector2& p_NewPosition, float p_Speed)
	: m_Texture{ LoadTexture(p_sTexturePath.c_str()) }
	, m_Position{ p_NewPosition }
	, m_fSpeed{ p_Speed }
{
}

const Texture2D& GraphicElement::getTexture()
{
	return m_Texture;
}

const Vector2& GraphicElement::getPosition()
{
	return m_Position;
}

void GraphicElement::setPosition(const Vector2& p_NewPosition)
{
	m_Position= p_NewPosition;
}

void GraphicElement::addToPosition(const Vector2& p_PositionOffset)
{
	m_Position = Vector2Add(m_Position, p_PositionOffset);
}

void GraphicElement::draw()
{
	DrawTexture(m_Texture, (int)m_Position.x, (int)m_Position.y, WHITE);
}

void GraphicElement::unloadTexture()
{
	UnloadTexture(m_Texture);       // Texture unloading
}
