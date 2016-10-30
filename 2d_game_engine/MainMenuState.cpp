#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "game.h"
#include "GameStateMachine.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include <assert.h>

const std::string MainMenuState::s_menuID = "MENU";

// Callbacks
void MainMenuState::s_menuToPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	Game::Instance()->quit();
}

// end callbacks

void MainMenuState::update()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		s_menuToPlay();
	}


	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
				m_gameObjects[i]->update();
		}
	}
}

void MainMenuState::render()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool MainMenuState::onEnter()
{
	// parse the state
	StateParser stateParser;
	stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;
	m_isCurrent = true;
	std::cout << "entering MenuState\n";
	return true;
}

bool MainMenuState::onExit()
{
	m_exiting = true;
	m_isCurrent = false;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();

	for(int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	
	m_textureIDList.clear();

	m_callbacks.clear();
	// reset the input handler
	//InputHandler::Instance()->reset();

	std::cout << "exiting MenuState\n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

