#include "title_scene.hpp"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "audio/include/AudioEngine.h"

#include "game/scenes/menu/menu_scene.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* title_scene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = title_scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
 

// on "init" you need to initialize your instance
bool title_scene::init()
{
	_fading = false;
	_loaded = false; 

    //////////////////////////////
    // 1. super init first
    if ( !layout::init(cocos2d::Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
		
	auto rootNode = CSLoader::createNode("game/scenes/title/main.csb");
	auto timeline = CSLoader::createTimeline("game/scenes/title/main.csb");

	timeline->play("main", true);

	rootNode->runAction(timeline);

	addChild(rootNode, rootNode->getZOrder(), "scene");

	// load objects

	auto audio = dynamic_cast<cocostudio::ComAudio*>(rootNode->getChildByName("audio")->getComponent("audio"));
	auto start = dynamic_cast<cocostudio::ComAudio*>(rootNode->getChildByName("start")->getComponent("start"));

	cocos2d::experimental::AudioEngine::preload(start->getFile());
	cocos2d::experimental::AudioEngine::preload(audio->getFile(), [this, audio, timeline](bool) {
		_loaded = true;
		auto audio_id = cocos2d::experimental::AudioEngine::play2d(audio->getFile(), audio->isLoop());
	});

	auto gyng =
		static_cast<cocos2d::ui::ImageView*>(rootNode->getChildByName("gyng"));

	gyng->setTouchEnabled(true);
	gyng->addTouchEventListener([this](cocos2d::Ref* image_view, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
			case cocos2d::ui::Widget::TouchEventType::BEGAN: {
				if (this->_fading == false && this->_loaded) {
					this->_fading = true;

					cocos2d::experimental::AudioEngine::stopAll();

					auto rootNode = this->getChildByName("scene");
					auto start =
						dynamic_cast<cocostudio::ComAudio*>(rootNode->getChildByName("start")->getComponent("start"));

					auto audio_id = cocos2d::experimental::AudioEngine::play2d(start->getFile(), start->isLoop());

					auto scene = menu_scene::createScene();
					auto fade = cocos2d::TransitionFade::create(0.50, scene, cocos2d::Color3B(0, 0, 0));

					cocos2d::Director::getInstance()->replaceScene(fade);

				}

			}

			break;
		}
	});

    return true;
}

