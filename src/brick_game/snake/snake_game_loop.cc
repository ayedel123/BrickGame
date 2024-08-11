
#include "snake_game_loop.h"

int SnakeGameLoop(s21::Snake &snake, WINDOW **windows)
{

    long long startTime = GetTimeInMS();
    long long endTime = 0;
    int is_end = 0;
    int keyVal = 0;
    int input = 0;
    GameState state = kStart;
    while (keyVal != 404 && state != kExitState)
    {
        input = UserInput();
        Signal signal = GetSignal(input);

        UpdateCurrentState(snake, &state, signal, windows);

        endTime = GetTimeInMS();
        if (state == kMoving &&
            endTime - startTime >=
                snake.game_info->speed - snake.game_info->level * snake.game_info->acceleration)
        {
            startTime = GetTimeInMS();
            UpdateCurrentState(snake, &state, snake.last_signal, windows);
        }
    }
    snake.body.clear();

    return 0;
}

void UpdateCurrentState(s21::Snake &snake, GameState *state,
                        Signal signal, WINDOW **windows)
{

    switch (*state)
    {

    case kStart:
        StartHandler(snake, state, signal, windows[kGameWin]);
        break;
    case kSpawnApple:
        SpawnAppleHandler(snake, state);
        break;
    case kMoving:
        MovingHandler(snake, state, signal, windows);
        break;
        break;
    case kGameOver:
        GameOverHandler(snake, state, signal, windows[kGameWin]);
        break;
    case kOnPause:
        PauseHandler(state, signal);
        break;
    case kExitState:
        ExitHandler(state);
        break;
    }
}