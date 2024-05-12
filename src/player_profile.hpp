#pragma once

#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/FriendsProfilePage.hpp"
#include "Geode/binding/ProfilePage.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/modify/FriendsProfilePage.hpp"
#include "Geode/ui/BasedButtonSprite.hpp"
#include "Geode/Enums.hpp"
#include "Geode/binding/GJUserScore.hpp"
#include "Geode/binding/ProfilePage.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/loader/Log.hpp"
#include "Geode/modify/ProfilePage.hpp"
#include "ratings_dict.hpp"
#include "ratings_profile.hpp"
#include <string>

using namespace geode::prelude;

class $modify(OwnProfilePageRatings, ProfilePage) {

    bool init(int accID, bool ownProfile) {
        if(!ProfilePage::init(accID, ownProfile)) {return false;}
        
        if (ownProfile) {
            auto menu = this->m_buttonMenu;

            auto spr = CircleButtonSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
            spr->setScale(0.7f);
            auto btn = CCMenuItemSpriteExtra::create(
                spr,
                this,
                menu_selector(OwnProfilePageRatings::onRatingsClick)
            );
            
            btn->setID("rating-button");
            btn->setPosition({408.f, -15.f});
            btn->setUserObject(this->m_score);

            menu->addChild(btn);
        }
        //log::debug("{}", pos->getID());
        

        return true;
    }

    void onRatingsClick(CCObject * sender);
};