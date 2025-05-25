#ifndef PADDLE_H
#define PADDLE_H

#pragma once
#include "raylib.h"

class Paddle {
protected:
    void LimitMovement();
public:
    float x, y;
    float width, height;
    int speed;

    virtual void Draw();
    virtual void Update(int ball_y = -1) = 0;
    virtual ~Paddle() = default;
};

#endif //PADDLE_H
