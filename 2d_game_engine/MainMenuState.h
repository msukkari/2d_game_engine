//
//  MenuState.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 09/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
//

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
public:
    
    virtual ~MainMenuState() {}

    virtual void update();
    virtual void render();
    
    virtual bool onEnter(); 
    virtual bool onExit(); 
    
    virtual std::string getStateID() const { return s_menuID; }
    
private:
    
    virtual void setCallbacks(const std::vector<Callback>& callbacks);
    
    // call back functions for menu items
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
    
	std::vector<std::string> m_textureIDList;
    std::vector<GameObject*> m_gameObjects;
};

#endif 
