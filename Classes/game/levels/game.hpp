#ifndef game_green_hill_a
#define game_green_hill_a

#include <utility>
#include <vector>
#include <string>
 
#include "cocos2d.h"
#include "windy/core/gameplay/layout.hpp"

namespace cocostudio {
	namespace timeline {
		class ActionTimeline;
	}
}

class game : windy::layout
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(game);

private:
	void notify_match(const bool& is_match);
	void trigger_color(const std::string& color);
	void create_beat(const std::string& beat_kind);

private:
	enum match_kind {
		match, 
		almost, 
	};

	class match {
	public:
		match(const std::string& color, const uint64_t& tag, const enum match_kind& match_kind) {
			this->_color = color;
			this->_tag = tag;
			this->_match_kind = match_kind;
		}

		std::string color() {
			return this->_color;
		}

		uint64_t tag() {
			return this->_tag;
		}

		enum match_kind match_kind() {
			return this->_match_kind;
		}

	private:
		std::string _color;
		uint64_t _tag;
		enum match_kind _match_kind;
	};

	class trigger {
	public:
		trigger(const std::string& color, const float& time) {
			this->_color = color;
			this->_time = time;
		}

		std::string color() {
			return this->_color;
		}

		float time() {
			return this->_time;
		}
	private:
		std::string _color;
		float _time;
	};

private:
	bool _playing;
	int  _audio_id;
	uint64_t _beat_tag_counter;

	cocos2d::Node* _hud;
	cocos2d::Node* _root_node;
	cocostudio::timeline::ActionTimeline* _hud_timeline;
	

	cocos2d::Vector<cocos2d::Node*> _beats;

	std::vector<std::shared_ptr<trigger> > _color_triggers; 


	std::vector<std::shared_ptr<class match> > _matches;

	uint32_t _match_combo;
	uint32_t _miss_combo;

	uint32_t _miss_combo_counter;
	std::map<std::string, uint32_t> _beat_combo_totals;
	std::map<std::string, uint32_t> _beat_combo_counters;

};

#endif // __HELLOWORLD_SCENE_H__
