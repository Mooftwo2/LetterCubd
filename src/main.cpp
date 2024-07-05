#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/utils/web.hpp>
#include <cstddef>
#include "ratings_profile.hpp"
#include "ratings_dict.hpp"
#include "player_profile.hpp"
#include "rating_popup.hpp"

using namespace geode::prelude;

class $modify(LetterCubdMenuLayer, MenuLayer) {

	bool init() {
		if (!MenuLayer::init())
			return false;
		
		auto winSize = CCDirector::get()->getWinSize();
		RatingsDictionary* mapInstance = RatingsDictionary::getInstance();

		auto saved = Mod::get()->getSavedValue<std::map<std::string,int>>("ratings");
		if(saved.empty()) {log::info("{}", "fuck you");}
		mapInstance->setRatings(saved);
		Mod::get()->setSavedValue("ratings", saved);
		
		/*
		for (const auto& pair : saved) {
			log::info("{}", pair.first); 
			log::info("{}", std::to_string(pair.second)); 
		}
		*/
		

		
	
		return true;
	}

	void onMyProfile(cocos2d::CCObject *sender) {
		auto account = GJAccountManager::get();
		auto id = account->m_accountID;
		OwnProfilePageRatings::create(id, true)->show();

	}
	

};


class $modify(LevelInfoWithRating, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;
        
        auto menu = CCMenu::create();
        menu->setID("rating-button");
		menu->setAnchorPoint({0.f, 0.f});
		menu->setPosition({0.f, 0.f});
		menu->ignoreAnchorPointForPosition(true);
		

        auto spr = CircleButtonSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
        spr->setScale(0.5f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(LevelInfoWithRating::onClick)
        );
        btn->setID("rating-button");
        btn->setUserObject(level);
    
       	menu->addChild(btn);
        this->addChild(menu);
        auto like_count = this->getChildByID("likes-label");
		btn->setPosition(like_count->getPosition() + CCPoint{(like_count->getContentWidth() * like_count->getScaleX()) + 15.f, 0.f});

        return true;
    }

    void onClick(CCObject* sender) {
        
        auto obj = static_cast<CCNode*>(sender)->getUserObject();
        auto lvl = static_cast<GJGameLevel*>(obj);
        RatingPopup::create(lvl)->show();

        
    }
};

