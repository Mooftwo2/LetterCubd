#pragma once

#include <Geode/Geode.hpp>

#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
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

        auto name = ButtonSprite::create("NAME");
        auto score = ButtonSprite::create("SCORE");
        auto difficulty = ButtonSprite::create("DIFFICULTY");
        auto lvlID = ButtonSprite::create("LEVEL ID");
        auto creator = ButtonSprite::create("CREATOR");
        auto feature = ButtonSprite::create("FEATURE");

        auto name_btn = CCMenuItemSpriteExtra::create(
            name,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(name_btn);
        
        auto score_btn = CCMenuItemSpriteExtra::create(
            score,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(score_btn);

        auto diff_btn = CCMenuItemSpriteExtra::create(
            difficulty,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(diff_btn);

        auto ID_btn = CCMenuItemSpriteExtra::create(
            lvlID,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(ID_btn);

        auto creator_btn = CCMenuItemSpriteExtra::create(
            creator,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(creator_btn);

        auto feature_btn = CCMenuItemSpriteExtra::create(
            feature,
            this,
            menu_selector(SortPopup::onSortSelect)
        );
        this->m_buttonMenu->addChild(feature_btn);
        
        return true;
    }

    void onSortSelect(CCObject * sender) {

    }


public:
    static SortPopup* create() {
        auto ret = new SortPopup();
        if (ret && ret->initAnchored(290.f, 180.f)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};






