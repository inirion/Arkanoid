#include "Funkcje.h"



Block::Block(int x, int y, int sizeX, int sizeY,BOOLEAN hit)
{
	this->coordinates.x = x;
	this->coordinates.y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->hitted = hit;
	
}
Block::~Block()
{
}

int Block::GetSizeX()const
{
	return this->sizeX;
}
int Block::GetSizeY()const
{
	return this->sizeY;
}
int Block::GetX()const
{
	return this->coordinates.x;
}
int Block::GetY()const
{
	return this->coordinates.y;
}
void Block::SetSizeX(int size)
{
	this->sizeX = sizeX;
}
void Block::SetSizeY(int size)
{
	this->sizeY = sizeY;
}
void Block::SetX(int x)
{
	this->coordinates.x += x;
}
void Block::SetY(int y)
{
	this->coordinates.y += y;
}
void Block::SetHit(BOOLEAN hit)
{
	this->hitted = hit;
}
BOOLEAN Block::GetHit()const
{
	return hitted;
}

void Block::DrawBlock(HDC hWinDC,HWND hwnd)
{
	blockBm = LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(ID_BLOCK));
	HDC hLocalDC;
	hLocalDC = CreateCompatibleDC(hWinDC);
	BITMAP qBitmap;
	GetObject(reinterpret_cast<HGDIOBJ>(blockBm), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, blockBm);
	BitBlt(hWinDC, GetX() - GetSizeX(), GetY() -GetSizeY(), GetX() + GetSizeX(), GetY() + GetSizeY(), hLocalDC, 0, 0, SRCCOPY);
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(blockBm);
}