#include <Windows.h>

class Block
{
public:
	Block(int x, int y, int sizeX, int sizeY,BOOLEAN hit);
	~Block();
	int GetX()const;
	int GetY()const;
	int GetSizeY()const;
	int GetSizeX()const;
	void SetX(int x);
	void SetY(int y);
	void SetSizeX(int size);
	void SetSizeY(int size);
	void SetHit(BOOLEAN hit);
	void DrawBlock(HDC hdcMem,HWND hwnd);
	BOOLEAN GetHit()const;
private:
	HBITMAP blockBm;
	BOOLEAN hitted;
	POINT coordinates;
	int sizeX;
	int sizeY;
};