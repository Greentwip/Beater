#ifndef game_menu_scene
#define game_menu_scene

#include <vector>
#include <string>

#include <map>
#include <memory>

#include "cocos2d.h"

#include "windy/core/gameplay/layout.hpp"

class menu_scene : windy::layout
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	
    // implement the "static create()" method manually
    CREATE_FUNC(menu_scene);

private:
	bool _fading;
	bool _loaded;
};

#endif // __HELLOWORLD_SCENE_H__
