#pragma once
// Local includes

// SDL includes
#include "SDL_pixels.h"

// std includes

static constexpr int GRID_ROWS = 30;
static constexpr int GRID_COLS = 30;
static constexpr int CELL_SIZE = 25;
static constexpr int GRID_Y_OFFSET = 120;
static constexpr SDL_Color GRID_COLOR{ 255, 255, 255, 255 };
static constexpr SDL_Color GRID_COLOR_ALT{ 190, 190, 190, 255 };

static constexpr SDL_Color SNAKE_BODY_COLOR{ 0, 140, 50, 255 };
static constexpr SDL_Color SNAKE_HEAD_COLOR{ 0, 62, 20, 255 };
static constexpr float SNAKE_MOVE_TIME_SECONDS = 0.2f;
static constexpr float SNAKE_MOVE_TIME_SECONDS_CAP = 0.1f; // the speed of the snake cannot drop below this value
static constexpr float SNAKE_SPEED_MODIFIER_PERCENT_PER_APPLE = 0.2f;

static constexpr int SCREEN_X_PADDING = 200;
static constexpr int SCREEN_Y_PADDING = 20;
static constexpr int SCREEN_WIDTH = GRID_COLS * CELL_SIZE + SCREEN_X_PADDING * 2;
static constexpr int SCREEN_HEIGHT = GRID_ROWS * CELL_SIZE + GRID_Y_OFFSET + SCREEN_Y_PADDING * 2;