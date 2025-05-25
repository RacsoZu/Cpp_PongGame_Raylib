#ifndef HUMANPADDLE_H
#define HUMANPADDLE_H

#include "Paddle.h"
#include "raylib.h"

class HumanPaddle : public Paddle {
private:
    KeyboardKey upKey;
    KeyboardKey downKey;
public:
    explicit HumanPaddle(KeyboardKey up = KEY_UP, KeyboardKey down = KEY_DOWN);
    void Update(int) override;
};

#endif //HUMANPADDLE_H
