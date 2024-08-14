
#include "snake_game_loop.h"

int SnakeGameLoop(s21::Snake &snake, WINDOW **windows)
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

        SnakeUpdateCurrentState(snake, &state, signal);

        endTime = GetTimeInMS();
        if (state == kMoving &&
            endTime - startTime >=
                snake.game_info->speed - snake.game_info->level * snake.game_info->acceleration)
        {
            startTime = GetTimeInMS();
            SnakeUpdateCurrentState(snake, &state, snake.last_signal);
        }
        printTetrisStats(windows[kInfoWin], snake.game_info, (state == kOnPause) ? 0 : 1);
        DrawGame(state, snake.game_info, windows);
    }
    snake.Clear();

    return 0;
}

void SnakeUpdateCurrentState(s21::Snake &snake, GameState *state,
                             Signal signal)
{

    switch (*state)
    {
    case kSpawnApple:
        SpawnAppleHandler(snake, state);
        break;
    case kMoving:
        MovingHandler(snake, state, signal);
        break;
    case kGameOver:
        GameOverHandler(snake, state, signal);
        break;
    case kOnPause:
        PauseHandler(state, signal);
        break;
    case kExitState:
        ExitHandler(snake, state);
        break;
    default:
        StartHandler(snake, state);
        break;
    }
}