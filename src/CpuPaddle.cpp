#include "CpuPaddle.h"

void CpuPaddle::Update(int ball_y) {
    if (y + height / 2 > ball_y) y -= speed;
    else y += speed;
    LimitMovement();
}

