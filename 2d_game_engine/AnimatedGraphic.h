#ifndef ANIMATED_GRAPHICS_H
#define ANIMATED_GRAPHICS_H

class LoaderParams;

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:

	AnimatedGraphic();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);

};

class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const 
	{
		return new AnimatedGraphic();
	}
};
#endif // !ANIMATED_GRAPHICS_H