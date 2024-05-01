#include "Geode/binding/GJGameLevel.hpp"
#include "Geode/binding/LevelInfoLayer.hpp"
#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/utils/cocos.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(LevelInfoWithRating, LevelInfoLayer) {

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;

        auto menu = CCMenu::create();
        auto spr = CircleButtonSprite::createWithSpriteFrameName("star_small01_001.png");
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(LevelInfoWithRating::onClick)
        );

        getChildOfType<CCLabelBMFont>(this, 2)->setID("like-count");
        auto like_count = this->getChildByID("like-count");

        menu->addChild(btn);
        menu->setPosition(like_count->getPosition() + CCPoint { 50.f, 0.f });
        this->addChild(menu);
        return true;
    }

    void onClick(CCObject* sender) {
        
        std::cout << "button clicked" << std::endl;
    }
};
