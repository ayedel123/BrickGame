#include "tetris_game_loop.h"

void DarwTetrisStats(GameState state, GameInfo *game_info, WINDOW **windows)
{
    if (state == kOnPause)
    {
        printTetrisStats(windows[kInfoWin], game_info, 0);
    }
    else
    {
        printTetrisStats(windows[kInfoWin], game_info, 1);
    }
}

int TetrisGameLoop(GameInfo *game_info, WINDOW **windows)
{

    long long startTime = GetTimeInMS();
    long long endTime = 0;
    int keyVal = 0;
    int input = 0;
    GameState state = kStart;

    while (keyVal != 404 && state != kExitState)
    {
        input = UserInput();
        Signal signal = GetSignalConsole(input);
        if (signal == kMoveUp)
            signal = kNosig;
        TetrisUpdateCurrentState(game_info, &state, signal);

        endTime = GetTimeInMS();
        if (state == kMoving &&
            endTime - startTime >=
                game_info->speed - game_info->level * game_info->acceleration)
        {
            startTime = GetTimeInMS();
            TetrisUpdateCurrentState(game_info, &state, kMoveDown);
        }
        DarwTetrisStats(state, game_info, windows);
        DrawGame(state, game_info, windows);
    }

    return 0;
}