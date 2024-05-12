#pragma once

#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/FriendsProfilePage.hpp"
#include "Geode/binding/ProfilePage.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/modify/FriendsProfilePage.hpp"
#include "Geode/ui/BasedButtonSprite.hpp"
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
protected:
    bool setup() override {
        this->setTitle("Your profile :)");

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
        return true;
    }

    void onExit(CCObject * sender);
        
    
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



