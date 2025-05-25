#include "Ball.h"
#include "GameState.h"
#include "SoundManager.h"

void Ball::Draw() {
    DrawCircle(x, y, radius, WHITE);
}

void Ball::Update() {

    x += speed_x;
    y += speed_y;
    if (y + radius >= GetScreenHeight()) {
        y = GetScreenHeight() - radius; // Correct position at bottom edge
        speed_y *= -1;
        PlaySound(SoundManager::ballCollision);
    } else if (y - radius <= 0) {
        y = radius;                     // Correct position at top edge
        speed_y *= -1;
        PlaySound(SoundManager::ballCollision);
    }

    if (x + radius >= GetScreenWidth()) {
        GameState::player1_score++;
        PlaySound(SoundManager::pointEarn);
        ResetBall();
        //Check if wins
        if (GameState::player1_score >= 6) {
            PlaySound(SoundManager::winSound);
            //Set player1 as the winner
            GameState::winner = GameState::Winner::Player1;
        }
    } else if (x - radius <= 0) {
        GameState::player2_score++;
        PlaySound(SoundManager::pointEarn);
        ResetBall();
        //Check if wins
        if (GameState::player2_score >= 6) {
            if (GameState::player2_cpu) {
                PlaySound(SoundManager::loseSound);
            }else {
                PlaySound(SoundManager::winSound);
            }
            //Set player2 as the winner
            GameState::winner = GameState::Winner::Player2;
        }
    }
}

void Ball::ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    int speed_choices[2] = {1, -1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
}
