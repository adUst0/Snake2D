#pragma once

// Local includes
#include "Utils.h"
#include "StateMachine.h"
#include "AssetManager.h"

// SDL includes
#include <SDL_rect.h>

// std includes
#include <string>
#include "SDLInitializer.h"

struct SDL_Window;
struct SDL_Renderer;

class Game : public NonCopyableAndNonMovable
{
public:
	static Game&					getInstance(const std::string& title = "Uninitialized", int width = 800, int height = 600);

	~Game();

	SDL_Renderer*					getRenderer() { return m_renderer; }
	AssetManager&					getAssetManager() { return m_textureManager; }
	StateMachine&					getStateMachine() { return m_stateMachine; }
	SDL_Point						getWindowSize() const;

	void							run();

	void							quit() { m_quit = true; }
private:
	Game(const std::string& title, int width, int height);

	SDLInitializer					m_SDLInitializer; // This has to be the first member variable. Explanation in header file

	SDL_Window*						m_window = nullptr;
	SDL_Renderer*					m_renderer = nullptr;

	AssetManager					m_textureManager;
	StateMachine					m_stateMachine;

	bool							m_quit = false;
};

