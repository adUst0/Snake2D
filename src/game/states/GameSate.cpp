// Local includes
#include "GameSate.h"
#include "engine/Game.h"

// SDL includes

// std includes

GameSate::GameSate(StateMachine& stateMachine)
	: SnakeBaseState(stateMachine)
{
	TTF_Font* font = Game::getInstance().getDefaultFont(24);
	if (font)
	{
		m_elapsedTimeText.initialize("Elapsed time ms: 0", *font);
		m_elapsedTimeText.setPosition({ SCREEN_X_PADDING, SCREEN_Y_PADDING });

		m_applesCollectedText.initialize("Apples collected: 0", *font);
		const int applesInfoYOffset = m_elapsedTimeText.getSprite().getTextureRectangle().h;
		m_applesCollectedText.setPosition({ SCREEN_X_PADDING, SCREEN_Y_PADDING + applesInfoYOffset + S_TEXT_OFFSSET });

		m_pauseInfoText.initialize("Press F5 to Pause/Unpause", *font);
		const int pauseInfoYOffset = applesInfoYOffset + m_applesCollectedText.getSprite().getTextureRectangle().h + S_TEXT_OFFSSET;
		m_pauseInfoText.setPosition({ SCREEN_X_PADDING, SCREEN_Y_PADDING + pauseInfoYOffset + S_TEXT_OFFSSET });
	}

	m_pauseText = Text::createTextCentered("PAUSED", Game::getInstance().getDefaultFont(72), { 255, 0, 0, 255 });

	AssetManager& assetManager = Game::getInstance().getAssetManager();
	assetManager.addTexture("controls", "assets/controls.jpg");
	if (SDL_Texture* texture = assetManager.getTexture("controls"))
	{
		m_controls.setTexture(*texture);
		m_controls.setPosition({ (int)m_world.getGrid().getCellPosition(GRID_ROWS - 1, GRID_COLS -1 ).x + CELL_SIZE - m_controls.getWidth(), SCREEN_Y_PADDING });
	}
}

void GameSate::handleInput()
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			Game::getInstance().quit();
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_F5)
			{
				m_isPaused = !m_isPaused;
			}
			else
			{
				KeyEvent keyEvent{ KeyEvent::Unknown };

				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					keyEvent = KeyEvent::Up;
					break;
				case SDLK_RIGHT:
					keyEvent = KeyEvent::Right;
					break;
				case SDLK_DOWN:
					keyEvent = KeyEvent::Down;
					break;
				case SDLK_LEFT:
					keyEvent = KeyEvent::Left;
					break;
				default:
					break;
				}

				m_world.onKeyPressed(keyEvent);
			}
		}
	}
}

void GameSate::update(float dtSeconds)
{
	if (m_isPaused)
	{
		return;
	}

	m_elapsedTime += dtSeconds;
	m_elapsedTimeSecondsTillNextUpdate -= dtSeconds;
	if (m_elapsedTimeSecondsTillNextUpdate <= 0)
	{
		m_elapsedTimeSecondsTillNextUpdate = m_elapsedTimeUpdateInterval;
		m_elapsedTimeText.setText("Elapsed time seconds: " + std::to_string(m_elapsedTime));
	}

	const int numApples = m_world.getSnake().numApplesCollected();
	m_world.tick(dtSeconds);
	if (m_world.getSnake().numApplesCollected() != numApples)
	{
		m_applesCollectedText.setText("Apples collected: " + std::to_string(m_world.getSnake().numApplesCollected()));
	}
}

void GameSate::draw()
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	m_background.draw(*renderer);
	m_elapsedTimeText.draw(*renderer);
	m_applesCollectedText.draw(*renderer);
	m_pauseInfoText.draw(*renderer);
	m_controls.draw(*renderer);

	m_world.draw(*renderer);

	if (m_isPaused)
	{
		m_pauseText.draw(*renderer);
	}

	SDL_RenderPresent(renderer);
}
