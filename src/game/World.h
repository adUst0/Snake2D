#pragma once
// Local includes
#include "Config.h"
#include "Grid.h"
#include "engine/Drawable.h"
#include "Apple.h"
#include "Snake.h"

// SDL includes

// std includes

struct SDL_Renderer;

class World : public Drawable
{
public:
	World();

	virtual void					draw(SDL_Renderer& renderer) const override;

	void							onKeyPressed(const KeyEvent& event);
	void							tick(float dtSeconds);

	Grid&							getGrid() { return m_grid; }
	const Grid&						getGrid() const { return m_grid; }

	const Snake&					getSnake() const { return m_snake; }

	void							moveAppleToRandomFreePosition();

	void							notifyGameOver();

private:
	Grid							m_grid;
	Apple							m_apple;
	Snake							m_snake;
};

