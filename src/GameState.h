
#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace GameState {
    inline int player1_score = 0;
    inline int player2_score = 0;
    inline bool player2_cpu = true;
    inline bool playAgain = true;
    enum class Winner { None = -1, Player1 = 0, Player2 = 1, Tie = 2 };
    inline Winner winner = Winner::None;
}

enum class Screen {
    Menu,
    HowToPlay,
    Game
};
#endif //GAMESTATE_H
