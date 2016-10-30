#include "Level.h"
#include "Layer.h"
#include <vector>
#include "TextureManager.h"

void Level::render()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

void Level::update()
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
}

void Level::exit()
{
	deleteTextures();
}

void Level::deleteTextures()
{
	for (int i = 0; i < m_textureNames.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureNames[i]);
	}
}