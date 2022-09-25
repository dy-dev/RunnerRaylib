#pragma once
#include <vector>
#include "GraphicElement.h"

class Background :
    public GraphicElement
{
protected:
	/**
	 * Background is composed of 2 identical graphics element that are drawn back to front
	 * to give an illusion of infinite scrolling
	 */
	std::vector<GraphicElement*> m_Components;
	
public:
	Background(const std::string& p_TexturePath, float p_Speed);
	virtual void update();
	virtual void draw();

};

