#include "SDL.h"
#include "Player.h"
#include "LoaderParams.h"
#include "InputHandler.h"

Player::Player() 
{

}

void Player::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}

void Player::draw()
{
	SDLGameObject::draw(false);
}

void Player::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));


	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_position.setX(m_position.getX() + 3);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_position.setX(m_position.getX() - 3);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_position.setY(m_position.getY() - 3);
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_position.setY(m_position.getY() + 3);
	}

	//this->handleInput();
	SDLGameObject::update();
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::handleInput()
{
	Vector2D* target = InputHandler::Instance()->getMousePosition();

	m_velocity = *target - m_position;

	m_velocity /= 50;
}

