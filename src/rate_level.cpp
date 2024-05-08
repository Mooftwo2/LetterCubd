#include "Geode/binding/GJGameLevel.hpp"
#include "Geode/binding/LevelInfoLayer.hpp"
#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/utils/SeedValue.hpp"
#include "Geode/utils/cocos.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include "rating_popup.hpp"

using namespace geode::prelude;

class $modify(LevelInfoWithRating, LevelInfoLayer) {

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;
        
        

        auto menu = CCMenu::create();
        menu->setID("rating-button");
        auto spr = CircleButtonSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
        spr->setScale(0.5f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(LevelInfoWithRating::onClick)
        );
        btn->setID("rating-button");
        btn->setUserObject(level);
    
       
        auto like_count = this->getChildByID("likes-label");
        //need to position button better
        menu->setPosition(like_count->getPosition() + CCPoint {like_count->getContentWidth() - 20.f, 0.f});
        menu->setContentSize({50.0f, 50.0f});
        
        
        menu->addChild(btn);
        this->addChild(menu);
        return true;
    }

    void onClick(CCObject* sender) {
        
        auto obj = static_cast<CCNode*>(sender)->getUserObject();
        auto lvl = static_cast<GJGameLevel*>(obj);
        RatingPopup::create(lvl)->show();

        
    }
};

