#pragma once

#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/FriendsProfilePage.hpp"
#include "Geode/binding/ProfilePage.hpp"
#include "Geode/binding/ScrollingLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/cocoa/CCArray.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/modify/FriendsProfilePage.hpp"
#include "Geode/ui/BasedButtonSprite.hpp"
#include "Geode/utils/cocos.hpp"
#include "ratings_dict.hpp"
#include "Geode/Enums.hpp"
#include "Geode/binding/GJUserScore.hpp"
#include "Geode/binding/ProfilePage.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/loader/Log.hpp"
#include "Geode/modify/ProfilePage.hpp"
#include "ratings_dict.hpp"
#include "player_profile.hpp"
#include <string>

using namespace geode::prelude;

class RatingProfile : public geode::Popup<> {

ScrollLayer* scroll = nullptr;

protected:
    bool setup() override {
        
        //TODO:
        /*
        Change this to "{username's} ratings depending on if its another user's profile"
        */
        this->setTitle("Your Ratings", "bigFont.fnt", 1.f);
        this->m_title->setColor(ccColor3B {255,255,255});

        auto layer = getChildOfType<CCLayer>(this, 0);

        auto old_btn = this->m_closeBtn;
        auto menu = this->m_buttonMenu;
        menu->removeChild(old_btn, true);
        auto back_button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_backBtn_001.png"),
            this,
            menu_selector(RatingProfile::onExit)
        );

        back_button->setPosition({old_btn->getPositionX() + 10.f, old_btn->getPositionY() - 10.f});
        menu->addChild(back_button);

        scroll = ScrollLayer::create(ccp(350, 180));
	    scroll->setAnchorPoint(ccp(0, 0));
	    scroll->ignoreAnchorPointForPosition(false);

        auto background = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
        background->setContentSize(scroll->getContentSize());
        background->setOpacity(75);
        background->setPosition(CCDirector::get()->getWinSize() / 2);
        this->addChild(background);
        background->addChild(scroll);
        
        getRatings();
        
        return true;

    }

    void onExit(CCObject * sender);
    void getRatings();
    
    


        
    
public:
    static RatingProfile* create() {
        auto ret = new RatingProfile();
        if (ret && ret->initAnchored(440.f, 290.f)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};



