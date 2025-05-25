#include <iostream>
#include <memory>
#include "raylib.h"
#include "GameState.h"
#include "UIUtils.h"
#include "SoundManager.h"
#include "Ball.h"
#include "HumanPaddle.h"
#include "CpuPaddle.h"
#include "Button.h"

//Global variables
Color GreenPantone = Color{0,133,90,255};
Color LightGreenPantone = Color{140,233,112,25};
Color DarkGreenPantone = Color{3,66,53,255};
Color redPantone = Color{174,24,50,255};
Screen currentScreen = Screen::Menu;

//Object Instances
HumanPaddle player1(KEY_UP, KEY_DOWN);
Ball ball;
std::unique_ptr<Paddle> player2;

int main() {
    //Screen Size
    constexpr int SCREEN_WIDTH = 1280;
    constexpr int SCREEN_HEIGHT = 800;

    //Initial Configs
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Game");
    SetTargetFPS(60);
    InitAudioDevice();
    SoundManager::Load();

    //Set window icon
    Image icon = LoadImage("assets/images/Icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    //Initial screen elements
    bool numPlayersSelected = false;
    Button onePlayerButton(SCREEN_WIDTH/3-30, SCREEN_HEIGHT-350, 200, 60,
        "One Player", 30, GreenPantone,     redPantone, WHITE);
    Button twoPlayersButton(SCREEN_WIDTH/3+260, SCREEN_HEIGHT-350, 200, 60,
        "Two Players", 30, GreenPantone, redPantone, WHITE);
    Button howToPlayButton(SCREEN_WIDTH/3+120, SCREEN_HEIGHT-250, 200, 60,
        "How to play", 30, GreenPantone, redPantone, WHITE);
    Button returnMenuButton(SCREEN_WIDTH/2-120, SCREEN_HEIGHT-150, 240, 60,
        "Back to menu", 30, GreenPantone, redPantone, WHITE);
    Image image = LoadImage("assets/images/PlayersControls.png");
    //Convert image to texture | image is loaded in RAM and Texture in Gpu RAM
    Texture2D controlsImage = LoadTextureFromImage(image);
    UnloadImage(image);

    //Initial screen
    while (!WindowShouldClose() && !numPlayersSelected) {
        BeginDrawing();
        ClearBackground(DarkGreenPantone);

        if(currentScreen == Screen::Menu) {
            DrawText("Pong Game", 192, 200, 170, WHITE);
            onePlayerButton.Draw();
            twoPlayersButton.Draw();
            howToPlayButton.Draw();
            DrawText("By: Racso", 1087, 730, 30, WHITE);

            //Check buttons
            if (onePlayerButton.IsClicked()) {
                numPlayersSelected = true;
                PlaySound(SoundManager::buttonSound);
                currentScreen = Screen::Game;
            }else if (twoPlayersButton.IsClicked()) {
                numPlayersSelected = true;
                PlaySound(SoundManager::buttonSound);
                GameState::player2_cpu = false; //The second player is not CPU
                currentScreen = Screen::Game;
            }else if (howToPlayButton.IsClicked()) {
                PlaySound(SoundManager::buttonSound);
                currentScreen = Screen::HowToPlay;
            }

        }else if(currentScreen == Screen::HowToPlay) {
            DrawCenteredText("How to play", 100, 160, WHITE);
            DrawText("Player 1", 275, SCREEN_HEIGHT/2-60, 50, GreenPantone);
            DrawText("Player 2", 796, SCREEN_HEIGHT/2-60, 50, redPantone);
            returnMenuButton.Draw();
            DrawTexture(controlsImage, 220, SCREEN_HEIGHT/2-30, WHITE);
            if(returnMenuButton.IsClicked()) {
                PlaySound(SoundManager::buttonSound);
                currentScreen = Screen::Menu;
            }
        }

        EndDrawing();
    }
    //Unload controls texture
    UnloadTexture(controlsImage);

    //Initial Objects Configs
    if(GameState::player2_cpu){
        player2 = std::make_unique<CpuPaddle>();
    }else{
        player2 = std::make_unique<HumanPaddle>(KEY_W, KEY_S);
    }

    ball.radius = 20;
    ball.speed_x = 10;
    ball.speed_y = 10;
    ball.x = GetScreenWidth() / 2;
    ball.y = GetScreenHeight() / 2;

    player1.width = 25;
    player1.height = 120;
    player1.speed = 8;
    player1.x = 10;
    player1.y = GetScreenHeight() / 2 - player1.height / 2;

    player2->width = 25;
    player2->height = 120;
    player2->speed = 8;
    player2->x = GetScreenWidth() - 35;
    player2->y = GetScreenHeight() / 2 - player2->height / 2;

    Rectangle player1Rect = {player1.x, player1.y, player1.width, player1.height};
    Rectangle player2Rect = {player2->x, player2->y, player2->width, player2->height};
    Vector2 ballPos = {ball.x, ball.y};

    //Main loop
    while (!WindowShouldClose() && GameState::playAgain) {
        BeginDrawing();
        //Check if game ends
        if(GameState::winner != GameState::Winner::None) {
            std::string winnerName = "None";
            if (GameState::winner == GameState::Winner::Player1) {
                winnerName = "Player 1";
            }else {
                winnerName = GameState::player2_cpu ? "CPU" : "Player 2";
            }
            ClearBackground(DarkGreenPantone);
            DrawCenteredText(TextFormat("%s Wins!", winnerName.c_str()), 230, 120, WHITE);
            DrawCenteredText("Press 'r' to play again or 'esc' to exit", 430, 40, WHITE);
            if(IsKeyDown(KEY_R)) {
                //Reset the scores and winner state
                GameState::player1_score = 0;
                GameState::player2_score = 0;
                GameState::winner = GameState::Winner::None;
                //Reset objects positions
                ball.x = GetScreenWidth() / 2;
                ball.y = GetScreenHeight() / 2;

                player1.x = 10;
                player1.y = GetScreenHeight() / 2 - player1.height / 2;

                player2->x = GetScreenWidth() - 35;
                player2->y = GetScreenHeight() / 2 - player2->height / 2;
            }
        }else {
            //Update moves
            ball.Update();
            player1.Update(-1); //Default value
            if (GameState::player2_cpu) {
                player2->Update(ball.y);
            }else {
                player2->Update(-1);
            }

            //Check for collisions
            ballPos.x = ball.x;
            ballPos.y = ball.y;

            player1Rect.x = player1.x;
            player1Rect.y = player1.y;
            player2Rect.x = player2->x;
            player2Rect.y = player2->y;

            if (CheckCollisionCircleRec(ballPos, ball.radius, player1Rect)) {
                ball.speed_x *= -1;
                // Move the ball just outside the player's paddle to avoid repeated collision
                ball.x = player1.x + player1.width + ball.radius;
                PlaySound(SoundManager::ballCollision);
            }else if (CheckCollisionCircleRec(ballPos, ball.radius, player2Rect)){
                ball.speed_x *= -1;
                ball.x = player2->x - ball.radius;
                PlaySound(SoundManager::ballCollision);
            }

            //Draw objects
            ClearBackground(GreenPantone);
            DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, WHITE);
            DrawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 150, LightGreenPantone);
            ball.Draw();
            player1.Draw();
            player2->Draw();
            DrawText(TextFormat("%i", GameState::player1_score), 300, 20, 80, WHITE);
            DrawText(TextFormat("%i", GameState::player2_score), 940, 20, 80, WHITE);
        }

        EndDrawing();
    }

    //De-Initialization
    SoundManager::Unload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}