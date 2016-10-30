#include "StateParser.h"
#include "game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

#include <iostream>
#include <vector>

using namespace std;

bool StateParser::parseState(const char *stateFile, string
	stateID, vector<GameObject *> *pObjects, vector<string>
	*pTextureIDs)
{
	TiXmlDocument xmlDoc;

	if (!xmlDoc.LoadFile(stateFile))
	{
		cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	// get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();
	// pre declare the states root node
	TiXmlElement* pStateRoot = 0;
	// get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
		e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
		}
	}
	// pre declare the texture root
	TiXmlElement* pTextureRoot = 0;
	// get the root of the texture elements
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}
	// now parse the textures
	parseTextures(pTextureRoot, pTextureIDs);
	// pre declare the object root node
	TiXmlElement* pObjectRoot = 0;

	// get the root node and assign it to pObjectRoot
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	// now parse the objects
	parseObjects(pObjectRoot, pObjects);
	return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot,
	vector<string> *pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		string filenameAttribute = e->Attribute("filename");
		string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute); // push into list
		TextureManager::Instance()->load(filenameAttribute,
			idAttribute, Game::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement *pStateRoot,
	std::vector<GameObject *> *pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		string textureID;
		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");
		GameObject* pGameObject = GameObjectFactory::Instance()
			->create(e->Attribute("type"));
		pGameObject->load(new LoaderParams
		(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}
