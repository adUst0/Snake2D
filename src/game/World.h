#pragma once
// Local includes
#include "Config.h"
#include "Grid.h"
#include "engine/Drawable.h"
#include "Apple.h"

// SDL includes

// std includes

struct SDL_Renderer;

class World : public Drawable
{
public:
	World();

	virtual void					draw(SDL_Renderer& renderer) const override;

	auto							getGrid() { return m_grid; }
	const auto						getGrid() const { return m_grid; }

	void							moveAppleToRandomFreePosition();

private:
	Grid<GRID_ROWS, GRID_COLS>		m_grid;
	Apple							m_apple;
};

