#include "GameOverState.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"

#include "GameObject.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

#include "StateParser.h"

#include "TextureManager.h"
#include "LoaderParams.h"
#include "game.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	//printf("fresh gameover update\n");
	//printf("updating MENUSTATE\n");
	for (int i = 0; i < m_gameObjects.size(); i++)
	{

		if (!m_gameObjects.size() > 10000)
			break;

			m_gameObjects[i]->update();

	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects,
		&m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);
	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_isCurrent = true;

	printf("ENTERING GAME OVER STATE\n");
	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();
	printf("%i\n", m_gameObjects.size());
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->
			clearFromTextureMap(m_textureIDList[i]);
	}

	printf("exiting GAMEOVERState\n");
	m_isCurrent = false;

	m_isCurrent = false;

	return true;
}

void GameOverState::s_gameOverToMain()
{
	Game::Instance()->getStateMachine()->popState();
	Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			// if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}