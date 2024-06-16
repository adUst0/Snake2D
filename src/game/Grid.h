#pragma once
// Local includes
#include "engine/Drawable.h"

// SDL includes
#include <SDL_render.h>
#include <vector>

// std includes

enum class CellStatus : int
{
	Free = 0,
	Snake,
	Apple,
	// TODO: obstacle
};

class Grid : public Drawable
{
public:
	Grid(int numRows, int numCols, int cellSize);

	int								rows() const { return m_numRows; }
	int								cols() const { return m_numCols; }
	bool							isValidCell(int row, int col) const;

	void							setColors(const SDL_Color& color, const SDL_Color& altColor);

	int								getCellSize() const { return m_cellSize; }

	void							setPosition(const SDL_Point& position) { m_position = position; }
	SDL_FPoint						getCellPosition(int row, int col) const;

	CellStatus						getCellStatus(int row, int col) const { return m_grid[row][col]; }
	void							setCellStatus(int row, int col, CellStatus cell);

	virtual void					draw(SDL_Renderer& renderer) const override;

private:
	int								m_numRows = 0;
	int								m_numCols = 0;
	std::vector<std::vector<CellStatus>> m_grid;

	SDL_Point						m_position{ 0, 0 };
	SDL_Color						m_color{ 255, 255, 255 };
	SDL_Color						m_altColor{ 190, 190, 190 };
	int								m_cellSize = 30;
};
