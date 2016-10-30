#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include "Layer.h"
#include <vector>

class GameObject;

class ObjectLayer : public Layer
{
public:
	void update();
	void render();
	void exit();



	std::vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}

private:
	std::vector<GameObject*> m_gameObjects;
};
#endif // !OBJECT_LAYER_H