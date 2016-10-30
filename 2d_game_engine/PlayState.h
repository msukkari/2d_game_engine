#ifndef PLAY_STATE_H
#define PLAY_STATE_H

class GameObject;
class SDLGameObject;
class Level;

#include "GameState.h"
#include <vector>

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;
	bool m_isCurrent;

	Level* pLevel;
};
#endif // !PLAY_STATE_H
