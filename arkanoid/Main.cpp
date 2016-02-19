#include <windows.h>
#include <ctime>
#include "Funkcje.h"
#include "resource.h"
#include <list>
#include <dos.h>
TCHAR AppName[] = L"Arkanoid - Help F1";

std::list <Block> block;
std::list <Block>::iterator it;
Paddle paddle;
Ball ball;
RECT r;
HBRUSH brush = static_cast<HBRUSH>(GetStockObject(DC_BRUSH));
HDC hdcMem;
HBITMAP hbmMem;
HANDLE hbmOld;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{


	switch (message)
	{
	case WM_CREATE: {
		GetClientRect(hwnd, &r);
		for (int i = 0;i < 40;i++)
		{
			if(i<10)
				block.push_back(Block(30+i*80,100, 20, 10, FALSE));
			if(i>=10 && i <20)
				block.push_back(Block(30 + (i-10) * 80, 150, 20, 10, FALSE));
			if(i>=20 && i <30)
				block.push_back(Block(30 + (i - 20) * 80, 200, 20, 10, FALSE));
			if(i>=30 && i<40)
				block.push_back(Block(30 + (i - 30) * 80, 250, 20, 10, FALSE));
		}
		paddle.initPaddle(r.right / 2, r.bottom - r.bottom*0.1, 16,100 ,15,hwnd);
		ball.initBall(r.right / 2, r.bottom - r.bottom*0.14, 10, 0,-8,hwnd);

		SetTimer(hwnd, 1, 16, NULL);
	}break;
	case WM_CHAR: {
		switch(wParam)
		{
		case ' ': {
			ball.SetVelocityX(0);
			ball.SetVelocityY(-10);
			ball.SetStart(TRUE);
		}break;
		}
	}break;

	case WM_PAINT: {
		PAINTSTRUCT ps;

		GetClientRect(hwnd, &r);
		BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(ps.hdc);
		hbmMem = CreateCompatibleBitmap(ps.hdc, r.right, r.bottom);
		hbmOld = SelectObject(hdcMem, hbmMem);
		SetDCBrushColor(ps.hdc,GRAY_BRUSH);
		FillRect(hdcMem, &r, brush);

		for (it = block.begin();it != block.end();++it)
			it->DrawBlock(hdcMem,hwnd);
		paddle.DrawPaddle(hdcMem, hwnd);
		ball.DrawBall(hdcMem, hwnd);
		
		BitBlt(ps.hdc, r.left, r.top, r.right, r.bottom, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		
	}break;
	case WM_TIMER: {

		switch (wParam)
		{
		case 1: {
			if (GetAsyncKeyState(VK_LEFT))//ruch w lewo paddle
			{
				
				if (paddle.GetX() - paddle.GetWidth()/2 - paddle.GetVelocity() > r.left)
				{
					paddle.SetX(-paddle.GetVelocity());
					if (ball.GetStart() == FALSE)
					{
						ball.SetX(-paddle.GetVelocity());

					}
				}
					
			}
			if (GetAsyncKeyState(VK_RIGHT))//ruch w prawo paddle
			{
				if (paddle.GetX() + paddle.GetWidth()/2 + paddle.GetVelocity() < r.right)
					paddle.SetX(paddle.GetVelocity());
				if (ball.GetStart() == FALSE)
				{
					ball.SetX(paddle.GetVelocity());

				}
			}
			

			if (ball.GetStart())
			{
				ball.SetY(ball.GetVelocityY());
				ball.SetX(ball.GetVelocityX());	
			}

			CollisionPaddleBall(paddle, ball, r);//kolizja z paddle
			CollisionRect(ball, paddle, r);//Kolizja z Rect
			
			for (it = block.begin();it != block.end();++it)
			{
				CollisionBlock(it, ball);
				if (it->GetHit()) it = block.erase(it);

			}
			InvalidateRect(hwnd, NULL, FALSE);
			
		}

				
		}break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hwnd, message, wParam, lParam));

		}
	}
	return (0L);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(nullptr));
	MSG msg = { 0 };
	WNDCLASS wndclass;
	HWND hwnd;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = AppName;

	if (RegisterClass(&wndclass) == 0)
		return FALSE;

	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, AppName, AppName, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^WS_MAXIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
		return FALSE;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{

		}
	}

	return static_cast<int>(msg.wParam);
}