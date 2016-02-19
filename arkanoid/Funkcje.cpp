#include "Funkcje.h"
#include <list>

void CollisionPaddleBall(Paddle &paddle, Ball &ball, RECT r)
{
	if (paddle.OnPaddleY(ball.GetY(), ball.GetSize(), ball.GetVelocityY()) && paddle.OnPaddleX(ball.GetX(), ball.GetSize(),ball.GetVelocityX())) {
		PlaySound(MAKEINTRESOURCE(ID_BLIP7), NULL, SND_RESOURCE | SND_ASYNC);
		float ballPos = ball.GetX() - paddle.GetX();
		float degree = (ballPos / (paddle.GetWidth()/4  - ball.GetSize()/2 ));
		ball.SetVelocityX(degree*2);
		ball.SetVelocityY(-ball.GetVelocityY());

	}

}
void CollisionRect(Ball &ball,Paddle &paddle, RECT r)
{
	if (ball.GetY() + ball.GetSize() >= r.bottom) {//odbicie od dolu
		PlaySound(MAKEINTRESOURCE(ID_GAMEOVER), NULL, SND_RESOURCE | SND_ASYNC);
		ball.Reset(r);
		paddle.Reset(r);
	}
	if (ball.GetY() - ball.GetSize() + ball.GetVelocityY() <= r.top) {//odbicie od gory
		PlaySound(MAKEINTRESOURCE(ID_JUMP), NULL, SND_RESOURCE | SND_ASYNC);
		ball.SetVelocityY(-ball.GetVelocityY());
		ball.SetVelocityX(ball.GetVelocityX());

	}
	if (ball.GetX() + ball.GetSize() +ball.GetVelocityX()>= r.right - 5)//odbicie od prawa
	{
		PlaySound(MAKEINTRESOURCE(ID_JUMP), NULL, SND_RESOURCE | SND_ASYNC);
		ball.SetVelocityX(-ball.GetVelocityX());
		ball.SetVelocityY(ball.GetVelocityY());
	}
	else if (ball.GetX() - ball.GetSize() + ball.GetVelocityX() <= r.left + 5)// odbicie od lewa
	{
		PlaySound(MAKEINTRESOURCE(ID_JUMP), NULL, SND_RESOURCE | SND_ASYNC);
		ball.SetVelocityX(-ball.GetVelocityX());
		ball.SetVelocityY(ball.GetVelocityY());
	}
}
void CollisionBlock(std::list<Block>::iterator &block,Ball &ball)
{
	if ((ball.GetX() + ball.GetVelocityX() + ball.GetSize() >= block->GetX() - block->GetSizeX() && ball.GetX() - ball.GetSize() + ball.GetVelocityX() <= block->GetX() + block->GetSizeX())
		&& (ball.GetY() + ball.GetVelocityY() + ball.GetSize() >= block->GetY() - block->GetSizeY() && ball.GetY() - ball.GetSize() + ball.GetVelocityY() <= block->GetY() + block->GetSizeY()))
	{
		if (ball.GetX() + ball.GetSize() < block->GetX() - block->GetSizeX() && ball.GetX() + ball.GetVelocityX() + ball.GetSize() >= block->GetX() - block->GetSizeX())
		{
			PlaySound(MAKEINTRESOURCE(ID_EXPLOSION6), NULL, SND_RESOURCE | SND_ASYNC);
			ball.SetVelocityX(-ball.GetVelocityX());
			block->SetHit(TRUE);
		}
		if (ball.GetX() - ball.GetSize() > block->GetX() + block->GetSizeX() && ball.GetX() + ball.GetVelocityX() - ball.GetSize() <= block->GetX() + block->GetSizeX())
		{
			PlaySound(MAKEINTRESOURCE(ID_EXPLOSION6), NULL, SND_RESOURCE | SND_ASYNC);
			ball.SetVelocityX(-ball.GetVelocityX());
			block->SetHit(TRUE);
		}

		if (ball.GetY() + ball.GetSize() < block->GetY() - block->GetSizeY() && ball.GetY() + ball.GetVelocityY() + ball.GetSize() >= block->GetY() - block->GetSizeY()) 
		{
			PlaySound(MAKEINTRESOURCE(ID_EXPLOSION6), NULL, SND_RESOURCE | SND_ASYNC);
			ball.SetVelocityY(-ball.GetVelocityY());
			block->SetHit(TRUE);
		}
		if (ball.GetY() - ball.GetSize() > block->GetY() + block->GetSizeY() && ball.GetY() + ball.GetVelocityY() - ball.GetSize() <= block->GetY() + block->GetSizeY())
		{
			PlaySound(MAKEINTRESOURCE(ID_EXPLOSION6), NULL, SND_RESOURCE | SND_ASYNC);
			ball.SetVelocityY(-ball.GetVelocityY());
			block->SetHit(TRUE);
		}
	}
		
}

