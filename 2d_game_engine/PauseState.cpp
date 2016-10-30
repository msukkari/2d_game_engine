#include "PauseState.h"
#include "game.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "StateParser.h"

#include <assert.h>

#include <stdio.h>
#include <string>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
	Game::Instance()->getStateMachine()->popState();
	Game::Instance()->getStateMachine()->changeState(new
		MainMenuState());
}
void PauseState::s_resumePlay()
{
	Game::Instance()->getStateMachine()->popState();
}
void PauseState::update()
{
	//printf("fresh pause update\n");
	//printf("updating PAUSESTATE\n");
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//printf("updating %s, %i\n", PauseState::s_pauseID,i);
		
		if (!m_gameObjects.size() > 10000)
			break;;

		if(!m_gameObjects[i] == NULL)
		{
			m_gameObjects[i]->update();
		}
		else
		{
			break;
		}

		//printf("updated PAUSESTATE\n");
	}
}
void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_pauseID, &m_gameObjects,
		&m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);
	setCallbacks(m_callbacks);

	printf("entering PauseState\n");
	m_isCurrent = true;
	return true;
}

bool PauseState::onExit()
{
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
	// reset the mouse button states to false
	//InputHandler::Instance()->reset();
	printf("exiting PauseState\n");
	m_isCurrent = false;
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>&
	callbacks)
{
	// go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
			{
				MenuButton* pButton =
					dynamic_cast<MenuButton*>(m_gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
	}
}
