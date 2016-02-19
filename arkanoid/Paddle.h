#include <Windows.h>

class Paddle
{
public:
	Paddle();
	~Paddle();
	void initPaddle(float x, float y, int height, int width, int velocity,HWND hwnd);
	float GetX()const;
	float GetY()const;
	int GetWidth()const;
	int GetHeight()const;
	int GetVelocity()const;
	void SetX(int x);
	void SetY(int y);
	void SetWidth(int size);
	void SetHeight(int size);
	void SetVelocity(int veloc);
	void DrawPaddle(HDC hdcMem, HWND hwnd);
	BOOLEAN OnPaddleX(float x, int size, int velocity);
	BOOLEAN OnPaddleY(float y, int size, int velocity);
	void Reset(RECT r);

private:
	HBITMAP paddleBm;
	POINT coordinates;
	int height;
	int width;
	int velocity;
};