#pragma once
#include <string>
#include <raylib.h>


class GraphicElement
{
protected:
	Texture2D m_Texture;
	Vector2 m_Position;
	float m_fWidth;
	float m_fHeight;
	float m_fSpeed;

public:
	GraphicElement();
	GraphicElement(const std::string& p_sTexturePath, float p_Speed);
	GraphicElement(const std::string& p_sTexturePath, const Vector2& p_NewPosition, float p_Speed);

	const Texture2D& getTexture();
	const Vector2& getPosition();
	virtual void setPosition(const Vector2& p_NewPosition);
	void addToPosition(const Vector2& p_PositionOffset);
	virtual void update() {};
	virtual void draw();
	float getWidth();
	float getHeight();

	void unloadTexture();
};

