#ifndef BALL_H
#define BALL_H

#include "raylib.h"

class Ball {
public:
    float x, y, radius;
    int speed_x, speed_y;

    void Draw();
    void Update();
    void ResetBall();
};


#endif //BALL_H
