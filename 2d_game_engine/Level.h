#ifndef LEVEL_H
#define LEVEL_H

class Layer;

#include <string>
#include <vector>

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level
{
public: 
	~Level() {};

	void update();
	void render();
	void exit();

	std::vector<Tileset>* getTilesets() { return &m_tilesets; }
	std::vector<Layer*>* getLayers() { return &m_layers; }

private:
	Level() {};
	friend class LevelParser;

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;

	std::vector<std::string> m_textureNames;

	void deleteTextures();
};
#endif // !LEVEL_H

