#include "raymath.h"

#include "GameManager.h"
#include "Background.h"

Background::Background(const std::string& p_TexturePath, float p_Speed)
	: GraphicElement(p_TexturePath, p_Speed)
{
	m_Components.push_back(this);
	m_Components.push_back(new GraphicElement(p_TexturePath, p_Speed));
	m_Components[1]->addToPosition(Vector2{ (float) m_Texture.width, 0 });
}

void Background::update()
{
	/**
	 * Each element is moved to the left at the defined speed
	 * When an element goes out of scope it is placed to the back of the other element
	 * taking into account the movement (hence the GameManager::getInstance()->getGameSpeed())
	 */
	for (auto elemnt : m_Components)
	{
		elemnt->setPosition(Vector2Subtract(elemnt->getPosition(), Vector2{m_fSpeed, 0}));
		if (elemnt->getPosition().x + elemnt->getTexture().width <= 0)
			elemnt->setPosition(Vector2{ (float)elemnt->getTexture().width - GameManager::getInstance()->getGameSpeed(), 0 });
	}
}


void Background::draw()
{
	for (auto elemnt : m_Components)
	{
		DrawTexture(elemnt->getTexture(), (int)elemnt->getPosition().x , 
			(int)elemnt->getPosition().y, WHITE);
	}
}
