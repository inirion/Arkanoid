#include "Funkcje.h"

Ball::Ball()
{
	this->coordinates.x = 0;
	this->coordinates.y = 0;
	this->size = 0;
	this->velocityX = 0;
	this->velocityY = 0;
	this->start = TRUE;
}
Ball::~Ball() {};
void Ball::initBall(int x, int y, int size, int velocityX, int velocityY, HWND hwnd)
{
	this->coordinates.x = x;
	this->coordinates.y = y;
	this->size = size;
	this->velocityY = velocityY;
	this->velocityX = velocityX;
	
}
int Ball::GetSize()const
{
	return this->size;
}
int Ball::GetX()const
{
	return this->coordinates.x;
}
int Ball::GetY()const
{
	return this->coordinates.y;
}
int Ball::GetVelocityX()const
{
	return this->velocityX;
}
int Ball::GetVelocityY()const
{
	return this->velocityY;
}
void Ball::SetSize(int size)
{
	this->size = size;
}
void Ball::SetX(int x)
{
	this->coordinates.x += x;
}
void Ball::SetY(int y)
{
	this->coordinates.y += y;
}
void Ball::SetVelocityX(int velocity)
{
	this->velocityX = velocity;
}
void Ball::SetVelocityY(int velocity)
{
	this->velocityY = velocity;
}
void Ball::Reset(RECT r)
{
	coordinates.x = r.right / 2;
	coordinates.y = r.bottom - r.bottom*0.135;
	velocityX = 0;
	velocityY = 0;
	start = FALSE;
}
BOOLEAN Ball::GetStart()const
{
	return start;
}
void Ball::SetStart(BOOLEAN s)
{
	start = s;
}
void Ball::DrawBall(HDC hdcMem, HWND hwnd)
{
	
	ballBm = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(ID_BALL));
	HDC hLocalDC;
	hLocalDC = CreateCompatibleDC(hdcMem);
	BITMAP qBitmap;
	GetObject(reinterpret_cast<HGDIOBJ>(ballBm), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, ballBm);
	BitBlt(hdcMem, GetX() - GetSize(), GetY() - GetSize(), GetX() + GetSize(), GetY() + GetSize(), hLocalDC, 0, 0, SRCCOPY);
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(ballBm);
}