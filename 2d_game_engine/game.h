#ifndef GAME_H
#define GAME_H



class GameObject;
class GameStateMachine;
struct SDL_Renderer;
struct SDL_Window;

#include <vector>

class Game
{
public:
	

	bool init(const char* title, int xpos, int ypos, int width, int
		height, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();

	bool running() { return m_bRunning; }
	void quit() { m_bRunning = false; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	static Game* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	int getGameWidth() { return m_gameWidth; }
	int getGameHeight() { return m_gameHeight; }

private:
	Game() {};
	~Game() {};

	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	GameStateMachine* m_pGameStateMachine;

	int m_currentFrame;
	bool m_bRunning;

	int m_gameWidth;
	int m_gameHeight;

	std::vector<GameObject*> m_gameObjects;
};
#endif // !GAME_H