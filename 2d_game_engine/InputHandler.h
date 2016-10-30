#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class Vector2D;

#include "SDL.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
	Vector2D* getMousePosition() { return m_mousePosition; }
	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);

	void update();
	void clean();

private:
	InputHandler();
	~InputHandler() {}

	//handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	const Uint8* m_keystates;


	static InputHandler* s_pInstance;
};
#endif // !INPUT_HANDLER_H