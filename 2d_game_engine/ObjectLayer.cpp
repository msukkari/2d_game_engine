#include "ObjectLayer.h"
#include "GameObject.h"


void ObjectLayer::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void ObjectLayer::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}


void ObjectLayer::exit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();
}