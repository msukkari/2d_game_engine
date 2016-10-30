#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "game.h"

#include "GameStateMachine.h"
#include "PauseState.h"
#include "GameOverState.h"

#include "GameObject.h"
#include "InputHandler.h"

#include "StateParser.h"
#include "LevelParser.h"
#include <string>
#include <stdio.h>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	//printf("%i", m_gameObjects.size());
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->getStateMachine()->pushState(new PauseState());
	}

	/*
	for (int i = 0; i < m_gameObjects.size(); i++)
	{

		if (!m_gameObjects.size() > 10000)
			break;

		m_gameObjects[i]->update();
	}

	if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
		dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	{
		Game::Instance()->getStateMachine()->pushState(new GameOverState());
	}

	*/

	pLevel->update();
}

void PlayState::render()
{
	pLevel->render();
}
bool PlayState::onEnter()
{
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/map1.tmx");

	printf("entering PlayState\n");
	m_isCurrent = true;

	return true;
}

bool PlayState::onExit()
{
	/*
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->
			clearFromTextureMap(m_textureIDList[i]);
	}

	m_textureIDList.clear();

	*/
	pLevel->exit();
	delete pLevel;

	printf("exiting PlayState\n");
	m_isCurrent = false;
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject*
	p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();
	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();
	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}