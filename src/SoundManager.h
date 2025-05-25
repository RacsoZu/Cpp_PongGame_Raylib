#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "raylib.h"

namespace SoundManager {
    inline Sound ballCollision;
    inline Sound pointEarn;
    inline Sound buttonSound;
    inline Sound winSound;
    inline Sound loseSound;

    inline void Load() {
        ballCollision = LoadSound("assets/sounds/BallCollision.wav");
        pointEarn = LoadSound("assets/sounds/PointEarn.wav");
        buttonSound = LoadSound("assets/sounds/ButtonSound.wav");
        winSound = LoadSound("assets/sounds/WinSound.wav");
        loseSound = LoadSound("assets/sounds/LoseSound.wav");
    }

    inline void Unload() {
        UnloadSound(ballCollision);
        UnloadSound(pointEarn);
    }
}

#endif //SOUNDMANAGER_H
