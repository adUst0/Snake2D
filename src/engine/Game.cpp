// Local includes
#include "Game.h"
#include "game/SplashState.h"

// SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// std includes
#include <iostream>
#include <memory>

Game::Game(const std::string& title, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cerr << "Window creation error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		std::cerr << "Error renderer creation";
		exit(1);
	}
}

Game& Game::getInstance(const std::string& title /*= "Uninitialized"*/, int width /*= 0*/, int height /*= 0*/)
{
	static Game game(title, width, height);
	return game;
}

Game::~Game()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

SDL_Point Game::getWindowSize() const
{
	SDL_Point point;
	SDL_GetWindowSize(m_window, &point.x, &point.y);
	return point;
}

void Game::run()
{
	m_stateMachine.pushState(std::make_unique<SplashState>(m_stateMachine));

	Uint32 lastUpdate = SDL_GetTicks();

	while (!m_quit)
	{
		m_stateMachine.processStateChanges();
		m_stateMachine.getActiveState()->handleInput();
		const Uint32 current = SDL_GetTicks();
		const float dtSeconds = (current - lastUpdate) / 1000.0f;
		m_stateMachine.getActiveState()->update(dtSeconds);
		lastUpdate = current;
		m_stateMachine.getActiveState()->draw();
	}
}
