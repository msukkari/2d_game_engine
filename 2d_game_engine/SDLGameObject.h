#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

class LoaderParams;

#include "GameObject.h"
#include "Vector2D.h"
#include <string>

class SDLGameObject : public GameObject
{
public:
	SDLGameObject();

	virtual void load(const LoaderParams* pParams);

	virtual void draw(bool face_left = true);
	virtual void update();
	virtual void clean();

	Vector2D getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	int m_numFrames;
	int m_animSpeed;

	std::string m_textureID;
};
#endif // !SDL_GAME_OBJECT_H