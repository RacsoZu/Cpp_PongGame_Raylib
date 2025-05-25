#include "HumanPaddle.h"

HumanPaddle::HumanPaddle(KeyboardKey up, KeyboardKey down)
    : upKey(up), downKey(down) {}

void HumanPaddle::Update(int) {
    if (IsKeyDown(upKey)) y -= speed;
    if (IsKeyDown(downKey)) y += speed;
    LimitMovement();
}

