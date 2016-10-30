#include "SDL.h"
#include "game.h"
#include "InputHandler.h"
#include "TextureManager.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	printf("game init attempt...\n");
	if (Game::Instance()->init("2D game", 100, 100, 1000, 480,
		false))
	{
		printf("game init success!\n");

		Uint32 frameStart, frameTime, time;
		bool texturePrinted = false; // Used to make sure that the number of texture is only printed once
		
		while (Game::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}

			if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_T) && !texturePrinted)
			{
				printf("Current number of textures loaded: %i\n", TextureManager::Instance()->getNumTextures());
				
				texturePrinted = true;
			}

			if (InputHandler::Instance()->isKeyUp(SDL_SCANCODE_T))
			{
				texturePrinted = false;
			}
		}
	}
	else
	{
		printf("game init failure - %s\n", SDL_GetError());
		return -1;
	}

	Game::Instance()->clean();

	return 0;
}

