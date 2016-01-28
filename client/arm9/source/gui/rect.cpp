#include <nds/arm9/video.h>	//SCREEN_WIDTH
#include <nds/dma.h>		//dmaFillHalfWords
#include <algorithm>
//std::min, std::max
#include "gui.h"

namespace D2K {namespace GUI {

Rect::Rect()
{
	Rect::m_x =
	Rect::m_y =
	Rect::m_w =
	Rect::m_h = 0;
}
Rect::Rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	int x_2 = x + w;
	int y_2 = y + h;
	if(x_2 >= SCREEN_WIDTH - 1)		//if x_2 is offscreen
		w = SCREEN_WIDTH - 1 - x;
	if(y_2 >= SCREEN_HEIGHT - 1)		//if y_2 is offscreen
		h = SCREEN_HEIGHT - 1 - y;
	Rect::m_x = x;
	Rect::m_y = y;
	Rect::m_w = w;
	Rect::m_h = h;
}
uint8_t Rect::GetX()
{
	return m_x;
}
void Rect::SetX(uint8_t x)
{
	Rect::m_x = x;
}
uint8_t Rect::GetY()
{
	return m_y;
}
void Rect::SetY(uint8_t y)
{
	Rect::m_y = y;
}
uint8_t Rect::GetW()
{
	return m_w;
}
void Rect::SetW(uint8_t w)
{
	int tempW = GetX() + w;
	if(tempW >= SCREEN_WIDTH - 1)//if tempW is offscreen
		Rect::m_w = SCREEN_WIDTH - 1 - GetX();
	else
		Rect::m_w = w;
}
uint8_t Rect::GetH()
{
	return m_h;
}
void Rect::SetH(uint8_t h)
{
	int tempH = GetY() + h;
	if(tempH >= SCREEN_HEIGHT - 1)//if tempH is offscreen
		Rect::m_h = SCREEN_HEIGHT - 1 - GetY();
	else
		Rect::m_h = h;
}
uint8_t Rect::GetX2()
{
	return m_x + m_w;
}
uint8_t Rect::GetY2()
{
	return m_y + m_h;
}
bool Rect::PointIntersect(uint8_t x, uint8_t y)
{
	return (x >= std::min((uint16_t)GetX(), (uint16_t)GetX2())
			&& x <= std::max((uint16_t)GetX(), (uint16_t)GetX2())
			&& y >= std::min((uint16_t)GetY(), (uint16_t)GetY2())
			&& y <= std::max((uint16_t)GetY(), (uint16_t)GetY2()));
}
Rect::~Rect() { }

}}//namespace D2K::GUI
