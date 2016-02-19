#include "Funkcje.h"

Paddle::Paddle()
{
	this->coordinates.x = 0;
	this->coordinates.y = 0;
	this->height = 0;
	this->width = 0;
	this->velocity = 0;
}
Paddle::~Paddle() {};
void Paddle::initPaddle(float x, float y, int height,int width, int velocity,HWND hwnd)
{
	this->coordinates.x = x;
	this->coordinates.y = y;
	this->height = height;
	this->width = width;
	this->velocity = velocity;
	
}
int Paddle::GetHeight()const
{
	return this->height;
}
int Paddle::GetWidth()const
{
	return this->width;
}
float Paddle::GetX()const
{
	return this->coordinates.x;
}
float Paddle::GetY()const
{
	return this->coordinates.y;
}
int Paddle::GetVelocity()const
{
	return this->velocity;
}
void Paddle::SetHeight(int size)
{
	this->height = size;
}
void Paddle::SetWidth(int size)
{
	this->width = size;
}
void Paddle::SetX(int x)
{
	this->coordinates.x += x;
}
void Paddle::SetY(int y)
{
	this->coordinates.y = y;
}
void Paddle::SetVelocity(int velocity)
{
	this->velocity = velocity;
}
BOOLEAN Paddle::OnPaddleX(float x,int size, int velocity)
{
	if (x + size + velocity >= coordinates.x - this->width/2 && x - size + velocity <= coordinates.x + this->width/2) return TRUE;
	return FALSE;
}
BOOLEAN Paddle::OnPaddleY(float y, int size, int velocity)
{
	if (y + size + velocity >= coordinates.y - this->height/2 && y + size + velocity <= coordinates.y +this->height/2) return TRUE;
	return FALSE;
}
void Paddle::Reset(RECT r)
{
	coordinates.x = r.right / 2;
	coordinates.y = r.bottom - r.bottom*0.1;
	velocity = 10;
}
void Paddle::DrawPaddle(HDC hdcMem,HWND hwnd)
{
	paddleBm = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(ID_PADDLE));
	HDC hLocalDC;
	hLocalDC = CreateCompatibleDC(hdcMem);
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, paddleBm);
	BitBlt(hdcMem, GetX()-GetWidth()/2, GetY() - GetHeight()/2 ,GetWidth(), GetHeight(), hLocalDC, 0, 0, SRCCOPY);
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(paddleBm);
}
