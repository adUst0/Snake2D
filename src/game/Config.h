#pragma once
#include "SDL_pixels.h"

static constexpr int GRID_ROWS = 30;
static constexpr int GRID_COLS = 30;
static constexpr int CELL_SIZE = 25;
static constexpr int GRID_Y_OFFSET = 100;
static constexpr SDL_Color GRID_COLOR{ 255, 255, 255, 255 };
static constexpr SDL_Color GRID_COLOR_ALT{ 190, 190, 190, 255 };

static constexpr SDL_Color SNAKE_COLOR{ 0, 140, 50, 255 };

static constexpr int SCREEN_X_PADDING = 200;
static constexpr int SCREEN_Y_PADDING = 20;
static constexpr int SCREEN_WIDTH = GRID_COLS * CELL_SIZE + SCREEN_X_PADDING * 2;
static constexpr int SCREEN_HEIGHT = GRID_ROWS * CELL_SIZE + GRID_Y_OFFSET + SCREEN_Y_PADDING * 2;