#include <windows.h>
#include "Paddle.h"
#include "resource.h"
#include "Ball.h"
#include "Block.h"
#include <list>
void CollisionPaddleBall(Paddle &paddle, Ball &ball, RECT r);
void CollisionRect(Ball &ball,Paddle &paddle, RECT r);
void CollisionBlock(std::list<Block>::iterator &block, Ball &ball);