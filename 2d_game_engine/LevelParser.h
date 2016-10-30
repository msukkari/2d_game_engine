#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

class Level;

#include "tinyxml\tinyxml.h"
#include <vector>
#include "Level.h"

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot,
		std::vector<Tileset>* pTilesets, Level* level);

	void parseTileLayer(TiXmlElement* pTileElement,
		std::vector<Layer*> *pLayers, const std::vector<Tileset>*
		pTilesets);

	void parseTextures(TiXmlElement* pTextureRoot, Level* level);
	void parseObjectLayer(TiXmlElement* pObjectElement,
		std::vector<Layer*> *pLayers);



	int m_tileSize;
	int m_width;
	int m_height;
};

#endif // !LEVEL_PARSER_H