#ifndef game_title_scene
#define game_title_scene

#include <vector>
#include <string>

#include <map>
#include <memory>

#include "cocos2d.h"

#include "windy/core/gameplay/layout.hpp"

class title_scene : windy::layout
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	
	void update(float delta);

    // implement the "static create()" method manually
    CREATE_FUNC(title_scene);

private:
	bool _fading;
	bool _loaded;
};

#endif // __HELLOWORLD_SCENE_H__
