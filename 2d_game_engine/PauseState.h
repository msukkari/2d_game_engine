#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

class GameObject;

#include "GameState.h"
#include "MenuState.h"
#include <vector>

class PauseState : public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static const std::string s_pauseID;


	static void s_pauseToMain();
	static void s_resumePlay();

	std::vector<std::string> m_textureIDList;
	std::vector<GameObject*> m_gameObjects;
};
#endif // !PAUSE_STATE_H