#include "game.hpp"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "audio/include/AudioEngine.h"

#include "game/scenes/menu/menu_scene.hpp"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = game::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool game::init()
{
  
	//////////////////////////////
	// 1. super init first
	if (!layout::init(cocos2d::Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	this->_playing = false;
	this->_audio_id = -1;
	this->_beat_tag_counter = 0;

	auto cache = SpriteFrameCache::getInstance();
	cache->removeUnusedSpriteFrames();

	this->scheduleUpdate();

	this->_root_node = CSLoader::createNode("game/levels/roller.csb");
	this->_hud_timeline = CSLoader::createTimeline("game/gui/hud.csb");
	this->_hud = this->_root_node->getChildByName("hud");


	auto audio = dynamic_cast<cocostudio::ComAudio*>(this->_root_node->getChildByName("audio")->getComponent("audio"));

	cocos2d::experimental::AudioEngine::preload(audio->getFile());


	auto loading_bar = static_cast<cocos2d::ui::LoadingBar*>(this->_hud->getChildByName("loading_bar"));

	this->_hud->runAction(this->_hud_timeline);

	this->_hud_timeline->gotoFrameAndPause(0);
	this->_hud_timeline->play("bar_pop_in", false);

	auto go_delay = cocos2d::DelayTime::create(1);
	auto two = cocos2d::CallFunc::create([this]() {
		auto counter = static_cast<cocos2d::ui::Text*>(this->_hud->getChildByName("counter"));

		counter->setString("2");
	});

	auto one = cocos2d::CallFunc::create([this]() {
		auto counter = static_cast<cocos2d::ui::Text*>(this->_hud->getChildByName("counter"));

		counter->setString("1");
	});

	auto go = cocos2d::CallFunc::create([this]() {
		auto counter = static_cast<cocos2d::ui::Text*>(this->_hud->getChildByName("counter"));

		counter->setString("");
	});

	auto start_sequence = cocos2d::Sequence::create(go_delay,
													go_delay, 
													two, 
													go_delay, 
													one, 
													go_delay, 
													go, nullptr);

	auto loading_tween = cocos2d::ActionTween::create(4, "progress", 100, 0);

	loading_bar->runAction(loading_tween);

	auto pop_out = cocos2d::CallFunc::create([this]() {
		this->_hud_timeline->play("bar_pop_out", false);
	});

	auto loading_out_delay = cocos2d::DelayTime::create(0.5f);


	auto blue	= static_cast<cocos2d::ui::Button*>(this->_hud->getChildByName("blue"));
	auto green	= static_cast<cocos2d::ui::Button*>(this->_hud->getChildByName("green"));
	auto yellow = static_cast<cocos2d::ui::Button*>(this->_hud->getChildByName("yellow"));
	auto purple = static_cast<cocos2d::ui::Button*>(this->_hud->getChildByName("purple"));

	auto show_buttons = cocos2d::CallFunc::create([this, blue, green, yellow, purple]() {

		this->_hud_timeline->play("buttons_pop_in", false);
		
		blue->addTouchEventListener([this](cocos2d::Ref* button, cocos2d::ui::Widget::TouchEventType type) {
			switch (type) {
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					this->trigger_color("blue");
				break;
			}

		});

		green->addTouchEventListener([this](cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type) {
			switch (type) {
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					this->trigger_color("green");
				break;
			}
		});

		yellow->addTouchEventListener([this](cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type) {
			switch (type) {
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					this->trigger_color("yellow");
				break;
			}
		});

		purple->addTouchEventListener([this](cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type) {
			switch (type) {
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					this->trigger_color("purple");
				break;
			}

		});


	});

	auto audio_callback = cocos2d::CallFunc::create([this, audio]() {
		this->_audio_id = cocos2d::experimental::AudioEngine::play2d(audio->getFile(), audio->isLoop());

		cocos2d::experimental::AudioEngine::setFinishCallback(this->_audio_id, 
			[this](int, const std::string&) {
			this->_hud_timeline->play("buttons_pop_out", false);
			this->_playing = false;

			auto scene = menu_scene::createScene();

			auto fade = cocos2d::TransitionFade::create(0.50, scene, cocos2d::Color3B(0, 0, 0));

			cocos2d::Director::getInstance()->replaceScene(fade);

		});

		this->_playing = true;
	});

	auto sequence = cocos2d::Sequence::create(start_sequence, 
											  pop_out, 
											  loading_out_delay, 
											  show_buttons, 
											  audio_callback, nullptr);

	this->addChild(this->_root_node);

	this->runAction(sequence);


	float start_time = 11.00f;	

	auto add_trigger = [this](const std::string& color, const float& time) {
		this->_color_triggers.push_back(std::make_shared<trigger>(color, time));
	};

	auto add_trigger_batch = [this, add_trigger, &start_time](const std::string& color,
												 const uint32_t& batch_size,
												 const float& increment) {

		auto time = this->_color_triggers.empty() ? start_time : this->_color_triggers.back()->time();

		for (unsigned int i = 0; i < batch_size; ++i) {
			time += increment;
			add_trigger(color, time);
		}

	};

	auto batch_begin = [this, add_trigger, &start_time](const std::string& color, const float& offset) {

		auto time = this->_color_triggers.empty() ? start_time : this->_color_triggers.back()->time();

		time  += offset;
		add_trigger(color, time);
	};

	auto add_mix_trigger_batch = [this, add_trigger, &start_time]
		(const std::vector<std::string>& colors,
			const uint64_t& batch_size,
			const float& increment) {

		auto time = this->_color_triggers.empty() ? start_time : this->_color_triggers.back()->time();

		for (unsigned int i = 0; i < batch_size; ++i) {
			auto turn = i % colors.size();
			time += increment;
			add_trigger(colors[turn], time);
		}

	};

	// all batches are generated with a separation of one second in between beats
	// identify the first beat second
	batch_begin("blue", 0.35f);	// offset from previous second
	add_trigger_batch("blue", 6, 1.00f);

	batch_begin("blue", 1.60f);	// offset from previous second
	add_trigger_batch("blue", 14, 1.00f);

	batch_begin("green", 1.60f);	// offset from previous second
	add_trigger_batch("green", 14, 1.00f);

	batch_begin("yellow", 1.60f);	// offset from previous second
	add_trigger_batch("yellow", 14, 1.00f);

	batch_begin("purple", 1.60f);	// offset from previous second
	add_trigger_batch("purple", 15, 1.00f);


	batch_begin("blue", 1.60f);

	add_mix_trigger_batch({ "green", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "green", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "yellow" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "yellow" }, 4, 0.5f);

	add_mix_trigger_batch({ "blue", "purple" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "purple" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "purple" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "purple" }, 4, 0.5f);

	add_mix_trigger_batch({ "blue", "yellow" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "yellow" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "yellow" }, 4, 0.5f);
	add_mix_trigger_batch({ "blue", "yellow" }, 4, 0.5f);

	add_mix_trigger_batch({ "green", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "green", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "green", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "green", "blue" }, 4, 0.5f);

	add_mix_trigger_batch({ "purple", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "purple", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "purple", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "purple", "blue" }, 4, 0.5f);
	add_mix_trigger_batch({ "purple", "blue" }, 4, 0.5f);

	add_trigger_batch("yellow", 8, 0.50f);

	batch_begin("green", 1.60f);

	add_trigger_batch("yellow", 2, 0.50f);

	batch_begin("green", 1.60f);
	add_trigger_batch("yellow", 2, 0.50f);

	batch_begin("green", 1.60f);
	add_trigger_batch("yellow", 3, 0.50f);

	add_trigger_batch("yellow", 22, 0.50f);

	return true;
}

void game::trigger_color(const std::string& color) {

	auto sound
		= dynamic_cast<cocostudio::ComAudio*>(this->_root_node->getChildByName(color)->getComponent(color));

	cocos2d::experimental::AudioEngine::play2d(sound->getFile(), sound->isLoop());


	//@TODO add score
	auto it = std::find_if(this->_beats.begin(), this->_beats.end(), [this](auto beat) {

		auto track_node = this->_hud->getChildByName("track_node");
		auto matcher = track_node->getChildByName("matcher");

		auto matcher_position = matcher->getPosition();
		auto beat_position = track_node->convertToNodeSpace(beat->getPosition());

		auto match_tolerance = 25;

		return	beat_position.x >= matcher_position.x - match_tolerance &&
				beat_position.x <= matcher_position.x + match_tolerance;
	});

	if (it != this->_beats.end()) { // means match, let's check the color
		if ((*it)->getName() == color) {

			// let's find if previously matched

			auto tag = (*it)->getTag();

			auto previous_it = std::find_if(this->_matches.begin(), this->_matches.end(), [&tag](auto match) {
				return tag == match->tag();
			});

			// in the case this is a new match we push back, for score
			if (previous_it == this->_matches.end()) {
				this->_matches.push_back(std::make_shared<match>(color, (*it)->getTag(), match_kind::match));
				this->_hud_timeline->play("match", false);
			}
			
		}
	}

	/*if (this->_track_record_enabled) {
		auto time = cocos2d::experimental::AudioEngine::getCurrentTime(this->_audio_id);

		// it takes 3.8 seconds for the beat to reach the match
		this->_color_triggers.push_back(std::make_shared<trigger>(color, time)); 
	}*/
	

}

void game::create_beat(const std::string& beat_kind) {

	std::string beat_name = beat_kind + "_" + "match";

	auto match = static_cast<cocos2d::ui::LoadingBar*>(this->_hud->getChildByName(beat_name));

	auto beat = match->clone();

	this->_beats.pushBack(beat);
	this->_root_node->addChild(beat);

	auto move_by = cocos2d::MoveBy::create(6, cocos2d::Vec3(this->getContentSize().width * -1.5, 0, 0));

	auto remove_beat = cocos2d::CallFunc::create([this, beat]() {
		this->_beats.eraseObject(beat);
		this->_root_node->removeChild(beat);
	});

	auto match_sequence = cocos2d::Sequence::create(move_by, remove_beat, nullptr);

	beat->setTag(this->_beat_tag_counter++);
	beat->setName(beat_kind);
	beat->runAction(match_sequence);	
}

void game::update(float dt) {

	auto start_key = this->_joypad->get_key(windy::key::codes::start);
	if (this->_playing) {

		auto audio_time = cocos2d::experimental::AudioEngine::getCurrentTime(this->_audio_id);

		std::vector<std::shared_ptr<trigger> > nuked_triggers;

		for (auto trigger : this->_color_triggers) {
			auto trigger_time = trigger->time();

			if (trigger_time <= audio_time + 4.0f) {
				this->create_beat(trigger->color());
				nuked_triggers.push_back(trigger);
			}

		}

		for (auto trigger : nuked_triggers) {
			auto it = std::find(this->_color_triggers.begin(), this->_color_triggers.end(), trigger);
			this->_color_triggers.erase(it);
		}


	}
}