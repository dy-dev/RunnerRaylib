#include <raylib.h>
#include "GraphicElement.h"

class UI:public GraphicElement
{
public:
	UI(const Vector2& p_ScreenDimension);
	virtual void draw() override;
	Font m_Font;

protected:
private:
	Vector2 m_ScreenDimension;
};
