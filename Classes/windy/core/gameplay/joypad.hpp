#ifndef windy_joypad
#define windy_joypad

#include <map>
#include <memory>

#include "cocos2d.h"

#include "key.hpp"

namespace windy {

	class joypad : public cocos2d::Node {
	public:
		virtual bool init() {

			if (!Node::init()) {
				return false;
			}

			
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_Z] = key::codes::a;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_X] = key::codes::b;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_C] = key::codes::c;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_V] = key::codes::d;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_ENTER] = key::codes::start;

			_maps[cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW] = key::codes::up;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW] = key::codes::down;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW] = key::codes::left;
			_maps[cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = key::codes::right; 

			for (auto mapping : _maps) {
				_keys[mapping.second] = std::make_shared<key>();
			}

			auto listener = cocos2d::EventListenerKeyboard::create();
			listener->onKeyPressed = CC_CALLBACK_2(joypad::onKeyPressed, this);
			listener->onKeyReleased = CC_CALLBACK_2(joypad::onKeyReleased, this);

			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


			scheduleUpdateWithPriority(1024); // largest priority possible to ensure it cleans keys in the end

			return true;
		}

		std::shared_ptr<key> get_key(key::codes code) {
			
			if (_keys.find(code) != _keys.end()) {
				return _keys[code];
			} else {
				return nullptr;
			}
		}

		CREATE_FUNC(joypad);


	private:
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*) {


			if (_maps.find(keyCode) != _maps.end()) {
				auto key = _keys[_maps[keyCode]];

				if (key) {
					key->_status = key::status::down;
					key->_pressed = true;
				}

			}


		}

		void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*) {

			if (_maps.find(keyCode) != _maps.end()) {
				auto key = _keys[_maps[keyCode]];

				if (key) {
					key->_status = key::status::up;
					key->_released = true;
				}
			}

		}


		void update(float dt) {

			for (auto keymap : _keys) {
				auto key = keymap.second;

				if (key->_pressed) {
					key->_pressed = false;
				}

				if (key->_released) {
					key->_released = false;
				}
			}

		}


	private:
		std::map<key::codes, std::shared_ptr<key> > _keys;
		std::map<cocos2d::EventKeyboard::KeyCode, key::codes> _maps;
	};

}



#endif