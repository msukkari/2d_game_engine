#include "MenuButton.h"
#include "InputHandler.h"
#include "LoaderParams.h"

MenuButton::MenuButton()
{
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (InputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;
			
			
			//printf("CHANGING STATES\n");
			if (m_callback != 0)
			{
				m_callback();
			}
			//printf("CHANGED STATES\n");

			//m_bReleased = false;
		}
		else if (!InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}

	//printf("END OF UPDATE\n");
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}