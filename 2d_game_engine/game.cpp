#include "SDL.h"
#include "SDL_image.h"
#include "game.h"
#include "Enemy.h"
#include "Player.h"
#include "AnimatedGraphic.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "PlayState.h"

#include <stdio.h>

Game* Game::s_pInstance = NULL;


bool Game::init(const char* title, int xpos, int ypos, int width, int
	height, bool fullscreen)
{

	m_gameHeight = height;
	m_gameWidth = width;

	//init SDL
////////////////////////////////////////////////////////////////////////////////
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		printf("SDL init success\n");
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,
			width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			printf("window creation success\n");
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				printf("renderer creation success\n");
				SDL_SetRenderDrawColor(m_pRenderer,
					135, 206, 235, 255);
			}
			else
			{
				printf("renderer init fail\n");
				return false; // renderer init fail
			}
		}
		else
		{
			printf("window init fail\n");
			return false; // window init fail
		}
	}
	else
	{
		printf("SDL init fail\n");
		return false; // SDL init fail
	}
	printf("init success\n");
/////////////////////////////////////////////////////////////////////////////////////////

	m_bRunning = true; // everything inited successfully,


	GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());


	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());	



}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);

}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::clean()
{
	printf("cleaning game\n");

	InputHandler::Instance()->clean();

	m_pGameStateMachine->clean();
	delete m_pGameStateMachine;

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}

