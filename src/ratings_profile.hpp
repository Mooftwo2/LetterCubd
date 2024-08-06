#pragma once

#include <Geode/Geode.hpp>

#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/touch_dispatcher/CCTouchDispatcher.h"
#include "Geode/ui/BasedButtonSprite.hpp"
#include "ratings_dict.hpp"
#include "player_profile.hpp"
#include <string>

using namespace geode::prelude;

class RatingProfile : public geode::Popup<> {

ScrollLayer* scroll = nullptr;
int pageNum;
//CCMenu* menu = nullptr;

protected:
    bool setup() override {
        
        //TODO:
        /*
        Change this to "{username's} ratings depending on if its another user's profile"
        */

        pageNum = 0;

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
        

        auto sort_sprite = AccountButtonSprite::createWithSpriteFrameName("GJ_filterIcon_001.png");
        auto sort_button = CCMenuItemSpriteExtra::create(
            sort_sprite,
            this,
            menu_selector(RatingProfile::onSort)
        );
        menu->addChild(sort_button);

        sort_button->setPositionX(menu->getContentWidth() / 2);
        sort_button->setPositionY(15.f);


        setupPageInitial();
        
        return true;

    }

    
    void onSort(CCObject * sender);
    void onLeft(CCObject * sender);
    void onRight(CCObject * sender);
    void onExit(CCObject * sender);
    void setupPageInitial();
    void setupPage(int pageNum);
    void sortRatings(std::vector<RatingInfo> *data, std::string filter);
    

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


class SortPopup : public geode::Popup<> {
protected:
    bool setup() override {
        this->setTitle("Sort Ratings by:", "bigFont.fnt", 1.f);
        this->m_title->setPositionY(this->m_title->getPositionY() - 5.f);

        auto name = ButtonSprite::create("NAME", 100, 1, 1.f, true);

        auto score = ButtonSprite::create("SCORE", 100, 1, 1.f, true);
        
        auto difficulty = ButtonSprite::create("DIFFICULTY", 100, 1, 1.f, true);
       
        auto lvlID = ButtonSprite::create("LEVEL ID", 100, 1, 1.f, true);
       
        auto creator = ButtonSprite::create("CREATOR", 100, 1, 1.f, true);
        
        auto feature = ButtonSprite::create("FEATURE", 100, 1, 1.f, true);
       

        auto name_btn = CCMenuItemSpriteExtra::create(
            name,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
       
        this->m_buttonMenu->addChild(name_btn);
        name_btn->setPositionX((this->m_mainLayer->getContentWidth() / 2) - 75.f);
        name_btn->setPositionY(110.f);
        name_btn->setTag(4);
        
        auto score_btn = CCMenuItemSpriteExtra::create(
            score,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(score_btn);
        score_btn->setPositionX((this->m_mainLayer->getContentWidth() / 2) + 75.f);
        score_btn->setPositionY(110.f);
        score_btn->setTag(0);

        auto diff_btn = CCMenuItemSpriteExtra::create(
            difficulty,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(diff_btn);
        diff_btn->setPositionX((this->m_mainLayer->getContentWidth() / 2) - 75.f);
        diff_btn->setPositionY(70.f);
        diff_btn->setTag(2);

        auto ID_btn = CCMenuItemSpriteExtra::create(
            lvlID,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(ID_btn);
        ID_btn->setPositionX((this->m_mainLayer->getContentWidth() / 2) + 75.f);
        ID_btn->setPositionY(70.f);
        ID_btn->setTag(1);

        auto creator_btn = CCMenuItemSpriteExtra::create(
            creator,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(creator_btn);
        creator_btn->setPositionX((this->m_mainLayer->getContentWidth() / 2) - 75.f);
        creator_btn->setPositionY(30.f);
        creator_btn->setTag(5);

        auto feature_btn = CCMenuItemSpriteExtra::create(
            feature,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(feature_btn);
        feature_btn->setPositionX((this->m_mainLayer->getContentWidth() / 2) + 75.f);
        feature_btn->setPositionY(30.f);
        feature_btn->setTag(3);
        return true;
    }

    void onSortSelect(CCObject * sender);

    

    void registerWithTouchDispatcher() override {
        CCTouchDispatcher::get()->addTargetedDelegate(this, -507, true);
        handleTouchPriority(this);
    }


public:
    static SortPopup* create() {
        auto ret = new SortPopup();
        if (ret && ret->initAnchored(300.f, 180.f)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};






