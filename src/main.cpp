#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/MenuLayer.hpp>
#include <cstddef>
#include "player_profile.hpp"
#include "ratings_dict.hpp"

using namespace geode::prelude;

class $modify(LetterCubdMenuLayer, MenuLayer) {
	CCLabelBMFont *label;
	
	bool init() {
		if (!MenuLayer::init())
			return false;
		
		auto winSize = CCDirector::get()->getWinSize();
		RatingsDictionary* mapInstance = RatingsDictionary::getInstance();

		auto saved = Mod::get()->getSavedValue<std::map<int,int>>("ratings");
		if(saved.empty()) {log::info("{}", "fuck you");}
		
		//Mod::get()->setSavedValue("ratings", saved);
		
		for (const auto& pair : saved) {
			log::info("{}", std::to_string(pair.first)); 
			log::info("{}", std::to_string(pair.second)); 
		}
		
		
		
		//mapInstance->setRatings(saved);

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
