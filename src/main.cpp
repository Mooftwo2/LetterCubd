#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/MenuLayer.hpp>
#include "player_profile.hpp"

using namespace geode::prelude;

class $modify(LetterCubdMenuLayer, MenuLayer) {
	CCLabelBMFont *label;
	bool init() {
		if (!MenuLayer::init())
			return false;

		auto winSize = CCDirector::get()->getWinSize();

		label = CCLabelBMFont::create("Hello, World!", "bigFont.fnt");
		label->setPosition(winSize / 2);
		this->addChild(label);
		
	
		return true;
	}

	void onMyProfile(cocos2d::CCObject *sender) {
		auto account = GJAccountManager::get();
		auto id = account->m_accountID;
	
		OwnProfilePageRatings::create(id, true)->show();

	}
};
