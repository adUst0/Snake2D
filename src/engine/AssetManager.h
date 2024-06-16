#pragma once

// Local includes
#include "Utils.h"

// SDL includes
#include <SDL_ttf.h>

// std includes
#include <unordered_map>
#include <string>

struct SDL_Texture;

class Game;

class AssetManager : public NonCopyableAndNonMovable
{
public:
	~AssetManager();

	void							addTexture(const std::string& key, const std::string& path);
	SDL_Texture*					getTexture(const std::string& key);

	void							addFont(const std::string& key, const std::string& path, int ptsize);
	TTF_Font*						getFont(const std::string& key, int ptsize);

private:
	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::unordered_map<std::string, TTF_Font*> m_fonts;
};

