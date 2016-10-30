#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class LoaderParams;




#include <stdio.h>

class GameObject
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual void load(const LoaderParams* pParams) = 0;
	virtual ~GameObject() {}

protected:

	GameObject() {}
	

};
#endif // !GAME_OBJECT_H