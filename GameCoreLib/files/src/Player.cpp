#include "GameManager.h"
#include "Player.h"
#include "Obstacle.h"

Player::Player(const std::string& p_Texture, float p_Speed, int p_iNbColumns, int p_iNbLines)
	: GraphicElement(p_Texture, GameManager::getInstance()->getPlayerStartingPosition(), p_Speed)
	, m_bIsJumping{ false }
	, m_iNbSpritsByLine{ p_iNbColumns }
	, m_iNbLines{ p_iNbLines }
	, m_FrameRec{ }
	, m_iFrameCounter{ 0 }
	, m_iCurrentFrame{ 0 }
	, m_iScore{ 0 }
{
	m_FrameRec.width = (float)m_Texture.width / m_iNbSpritsByLine - 1;
	m_FrameRec.height = (float)m_Texture.height * 2 / (3 * m_iNbLines);
}

/**
 * Manage the frame to display, depending on the frame rate and jumping state
 */
void Player::update()
{
	m_iFrameCounter++;

	if (m_bIsJumping)
	{
		m_FrameRec.y = (float)m_Texture.height / m_iNbLines;
		if (m_iFrameCounter < 16)
		{
			m_FrameRec.x = 0;
			m_Position.y -= 8;
		}
		else if (m_iFrameCounter < 31)
		{
			m_FrameRec.x = (float)m_Texture.width / m_iNbSpritsByLine;
			m_Position.y += 8;
		}
		else
		{
			m_bIsJumping = false;
			m_iFrameCounter = 0;
			m_FrameRec.y = 0;
		}
	}
	else if (m_iFrameCounter >= (60 / m_fSpeed))
	{
		/**
		 * Every frame / speed we change the current frame selected on the sprite sheet
		 */
		m_iFrameCounter = 0;
		m_iCurrentFrame++;

		if (m_iCurrentFrame > (m_iNbSpritsByLine - 2)) m_iCurrentFrame = 0;

		m_FrameRec.x = (float)m_iCurrentFrame * (float)m_Texture.width / m_iNbSpritsByLine;
	}
}

void Player::draw()
{
	DrawTextureRec(m_Texture, m_FrameRec, m_Position, WHITE);  // Draw part of the texture
}

float Player::getHeight()
{
	return m_FrameRec.height;
}

void Player::manageInput()
{
	/**
	 * Space bar make the character jump if he not already in a jump state
	 */
	if (IsKeyPressed(KEY_SPACE) && !m_bIsJumping)
	{
		m_bIsJumping = true;
		m_iFrameCounter = 0;
	}
}

int Player::getScore() const 
{
	return m_iScore;
}

bool Player::isColliding(Obstacle* p_pObstacle)
{
	return CheckCollisionRecs({ getPosition().x, getPosition().y, m_FrameRec.width - 8, m_FrameRec.height - 8 },
			{ p_pObstacle->getPosition().x,p_pObstacle->getPosition().y,p_pObstacle->getWidth() - 8, p_pObstacle->getHeight() - 8 });
}

void Player::addPoints(int p_iPoints)
{
	m_iScore += p_iPoints;
}
