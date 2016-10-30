#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <string>

class LoaderParams
{
public:

	LoaderParams(int x, int y, int width, int height, std::string
		textureID, int numFrames, int callBackID = 0, int animSpeed = 0) : 
		m_x(x), 
		m_y(y), 
		m_width(width),
		m_height(height),
		m_textureID(textureID), 
		m_callbackID(callBackID),
		m_animSpeed(animSpeed),
		m_numFrames(numFrames)
	{

	}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getNumFrames() const { return m_numFrames; }
	int getAnimSpeed() const { return m_animSpeed; }
	int getCallbackID() const { return m_callbackID; }
	std::string getTextureID() const { return m_textureID; }

private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_numFrames;
	int m_animSpeed;

	int m_callbackID;

	std::string m_textureID;
};
#endif // !LOADER_PARAMS_H