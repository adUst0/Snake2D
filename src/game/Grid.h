#pragma once
// Local includes
#include "engine/Drawable.h"

// SDL includes
#include <SDL_render.h>

// std includes

enum class CellType
{
	Free = 0,
	Snake,
	Apple,
	// TODO: obstacle
};

template <int ROWS, int COLS>
class Grid : public Drawable
{
public:
	Grid(int cellSize);

	int								rows() const { return ROWS; }
	int								cols() const { return COLS; }

	void							setColors(const SDL_Color& color, const SDL_Color& altColor);

	int								getCellSize() const { return m_cellSize; }

	void							setPosition(const SDL_Point& position) { m_position = position; }
	SDL_FPoint						getCellPosition(int row, int col) const;

	CellType						getCellType(int row, int col) const { return m_grid[row][col]; }
	void							setCellType(int row, int col, CellType cell) { m_grid[row][col] = cell; }

	virtual void					draw(SDL_Renderer& renderer) const override;

private:
	CellType						m_grid[ROWS][COLS];
	SDL_Point						m_position{ 0, 0 };
	SDL_Color						m_color{ 255, 255, 255 };
	SDL_Color						m_altColor{ 190, 190, 190 };
	int								m_cellSize = 30;
};

template <int ROWS, int COLS>
Grid<ROWS, COLS>::Grid(int cellSize)
	: m_cellSize(cellSize)
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			m_grid[i][j] = CellType::Free;
		}
	}
}

template <int ROWS, int COLS>
SDL_FPoint Grid<ROWS, COLS>::getCellPosition(int row, int col) const
{
	return { (float)col * m_cellSize + m_position.x, (float)row * m_cellSize + m_position.y };
}

template <int ROWS, int COLS>
void Grid<ROWS, COLS>::setColors(const SDL_Color& color, const SDL_Color& altColor)
{
	m_color = color;
	m_altColor = altColor;
}

template <int ROWS, int COLS>
void Grid<ROWS, COLS>::draw(SDL_Renderer& renderer) const
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(&renderer, &r, &g, &b, &a);

	for (int i = 0; i < rows(); ++i)
	{
		for (int j = 0; j < cols(); ++j)
		{
			const SDL_Color& color = (i + j) % 2 == 0 ? m_color : m_altColor;
			SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
			const auto cellPos = getCellPosition(i, j);
			const SDL_FRect rect{ cellPos.x, cellPos.y, (float)m_cellSize, (float)m_cellSize};
			SDL_RenderFillRectF(&renderer, &rect);
		}
	}

	SDL_SetRenderDrawColor(&renderer, r, g, b, a);
}

