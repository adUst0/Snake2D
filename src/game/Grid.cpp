// Local includes
#include "Grid.h"

// SDL includes

// std includes

Grid::Grid(int numRows, int numCols, int cellSize)
	: m_numRows(numRows)
	, m_numCols(numCols)
	, m_cellSize(cellSize)
{
	std::vector<CellStatus> row(m_numCols, CellStatus::Free);
	m_grid = std::vector<std::vector<CellStatus>>(m_numRows, row);
}

void Grid::setCellStatus(int row, int col, CellStatus cell)
{
	m_grid[row][col] = cell;
}

bool Grid::isValidCell(int row, int col) const
{
	return row >= 0 && row < m_numRows && col >= 0 && col < m_numCols;
}

SDL_FPoint Grid::getCellPosition(int row, int col) const
{
	return { (float)col * m_cellSize + m_position.x, (float)row * m_cellSize + m_position.y };
}

void Grid::setColors(const SDL_Color& color, const SDL_Color& altColor)
{
	m_color = color;
	m_altColor = altColor;
}

void Grid::draw(SDL_Renderer& renderer) const
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
			const SDL_FRect rect{ cellPos.x, cellPos.y, (float)m_cellSize, (float)m_cellSize };
			SDL_RenderFillRectF(&renderer, &rect);
		}
	}

	SDL_SetRenderDrawColor(&renderer, r, g, b, a);
}