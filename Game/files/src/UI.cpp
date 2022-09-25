#include "UI.h"
#include "GameManager.h"
#include "Player.h"

UI::UI(const Vector2& p_ScreenDimension)
	:m_ScreenDimension{p_ScreenDimension}
	, m_Font{ LoadFontEx("assets/fonts/BADABB.TTF", 32, 0, 250) }
{
}

void UI::draw()
{
	int score = GameManager::getInstance()->getPlayer()->getScore();
	std::string playerScore = "  Score : " + std::to_string(score);
	auto measure = MeasureTextEx(m_Font, playerScore.c_str(), 40, 2);
	DrawRectangle(15,25, measure.x, measure.y, Fade(BLACK, 0.6f));
	DrawTextEx(m_Font, playerScore.c_str(),{ 20.0f, 30.0f }, (float)32, 2, YELLOW);
}
