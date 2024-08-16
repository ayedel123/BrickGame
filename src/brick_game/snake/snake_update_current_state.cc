#include "snake_update_current_state.h"

void SnakeUpdateCurrentState(s21::Snake &snake, GameState *state,
                             Signal signal) {
  switch (*state) {
    case kSpawn:
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
