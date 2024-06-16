// Local includes
#include "Game.h"
#include "AssetManager.h"

// SDL includes
#include <SDL.h>
#include <SDL_image.h>

// std includes
#include <iostream>


AssetManager::~AssetManager()
{
	for (auto& [_, texture] : m_textures)
	{
		SDL_DestroyTexture(texture);
	}

	for (auto& [_, font] : m_fonts)
	{
		TTF_CloseFont(font);
	}
}

void AssetManager::addTexture(const std::string& key, const std::string& path)
{
	if (getTexture(key))
	{
		return;
	}

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface)
	{
		std::cerr << "Error loading image: " << IMG_GetError();
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), surface);
	if (!texture)
	{
		std::cerr << "Error creating texture";
	}
	else
	{
		m_textures[key] = texture;
	}

	SDL_FreeSurface(surface);
}

SDL_Texture* AssetManager::getTexture(const std::string& key)
{
	auto iter = m_textures.find(key);
	return iter != m_textures.end() ? iter->second : nullptr;
}

void AssetManager::addFont(const std::string& key, const std::string& path, int ptsize)
{
	if (getFont(key, ptsize))
	{
		return;
	}

	TTF_Font* font = TTF_OpenFont(path.c_str(), ptsize);
	if (!font)
	{
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return;
	}

	const std::string keyWithSize = key + std::to_string(ptsize);
	m_fonts[keyWithSize] = font;
}

TTF_Font* AssetManager::getFont(const std::string& key, int ptsize)
{
	const std::string keyWithSize = key + std::to_string(ptsize);
	auto iter = m_fonts.find(keyWithSize);
	return iter != m_fonts.end() ? iter->second : nullptr;
}
