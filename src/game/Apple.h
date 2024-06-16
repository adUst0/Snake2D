#pragma once
// Local includes
#include "engine/Sprite.h"
#include "WorldTypes.h"

// SDL includes

// std includes

class World;

class Apple : public Drawable
{
public:
	Apple(World& world);

	virtual void					draw(SDL_Renderer& renderer) const override;

	void							setWorldPosition(const WorldPosition& pos);

private:
	World*							m_world = nullptr;

	Sprite							m_sprite;
	WorldPosition					m_worldPosition;
};

