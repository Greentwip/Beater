#include "opening_scene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

#include "game/scenes/title/title_scene.hpp"

//#include "ui/UIVideoPlayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* opening_scene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = opening_scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool opening_scene::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 255)) )
    {
        return false;
    }

	this->setCascadeOpacityEnabled(true);
    
    auto rootNode = CSLoader::createNode("game/scenes/opening/greentwip_logo.csb");
	auto timeline = CSLoader::createTimeline("game/scenes/opening/greentwip_logo.csb");

	timeline->gotoFrameAndPause(0);

	auto fade_in = cocos2d::FadeIn::create(1.0);

	auto audio_playback = cocos2d::CallFunc::create([this, rootNode, timeline]() {

		auto audio = dynamic_cast<cocostudio::ComAudio*>(rootNode->getChildByName("audio")->getComponent("audio"));

		auto audio_id = cocos2d::experimental::AudioEngine::play2d(audio->getFile(), audio->isLoop());

		cocos2d::experimental::AudioEngine::setFinishCallback(audio_id, [this, rootNode](int, const std::string&) {

			auto fade_out = cocos2d::FadeOut::create(1.0);

			auto transition = cocos2d::CallFunc::create([]() {
				auto scene = title_scene::createScene();
				cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(1.0, scene, cocos2d::Color3B(0, 0, 0)));
			});

			auto sequence = cocos2d::Sequence::create(fade_out, transition, nullptr);
			this->runAction(sequence);

		});

	});
	

	auto sequence = cocos2d::Sequence::create(fade_in, audio_playback, nullptr);

	rootNode->runAction(timeline);

	this->runAction(sequence);

	addChild(rootNode);

    return true;
}
