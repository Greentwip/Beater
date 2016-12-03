#ifndef windy_layout
#define windy_layout

#include "cocos2d.h"

#include "joypad.hpp"

namespace windy {

	class layout : public cocos2d::LayerColor {
	public:
		static cocos2d::Scene* createScene() = delete;
		virtual bool init(cocos2d::Color4B color = cocos2d::Color4B(0, 0, 0, 255)) {
			//////////////////////////////
			// 1. super init first
			if (!LayerColor::initWithColor(color))
			{
				return false;
			}

			_joypad = joypad::create();

			addChild(_joypad);

			return true;
		}

		void texture_preloader(std::vector<std::string> paths, const std::function<void()>& callback) {

			if (paths.empty()) {
				callback();
			}
			else {

				std::string path = paths.back();
				paths.pop_back();

				cocos2d::TextureCache::getInstance()->addImageAsync(path, [this, paths, callback](cocos2d::Texture2D* tex) {
					texture_preloader(paths, callback);
				});

			}
		}

	protected:
		joypad* _joypad;
	};
}


#endif