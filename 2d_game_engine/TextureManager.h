#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL.h"
#include <string>
#include <map>

class TextureManager
{
public:
	~TextureManager() { delete this; }


	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int
		height, int currentRow, int currentFrame, SDL_Renderer*
		pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int
		spacing, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer *pRenderer);

	static TextureManager* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void clearFromTextureMap(std::string id);

	int getNumTextures() { return m_textureMap.size(); }


private:
	TextureManager() {}

	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap;
};





#endif
