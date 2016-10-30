#include "AnimatedGraphic.h"
#include "SDL.h"

AnimatedGraphic::AnimatedGraphic()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed) % 2)));

	SDLGameObject::update();
}

void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}