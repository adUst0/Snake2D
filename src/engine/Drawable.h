#pragma once
// Local includes

// SDL includes

// std includes

struct SDL_Renderer;

class Drawable
{
	virtual void					draw(SDL_Renderer& renderer) const = 0;
};