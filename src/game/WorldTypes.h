#pragma once
// Local includes

// SDL includes

// std includes

struct WorldPosition
{
	int row = -1;
	int col = -1;
};

enum class KeyEvent
{
	Up = 0,
	Right,
	Down,
	Left,
	Unknown
};