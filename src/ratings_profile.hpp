#pragma once

#include <Geode/Geode.hpp>

#include "ratings_dict.hpp"
#include "player_profile.hpp"
#include <string>

using namespace geode::prelude;

class RatingProfile : public geode::Popup<> {

ScrollLayer* scroll = nullptr;
int pageNum;

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
        
    
        
        auto leftBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            this,
            menu_selector(RatingProfile::onLeft)
        );
        leftBtn->setID("left-button");
        menu->addChild(leftBtn);
        leftBtn->setPositionY(this->getContentHeight() / 2);
        leftBtn->setPositionX(this->getPositionX() + 25.f);

        auto rightBtn  = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            this,
            menu_selector(RatingProfile::onRight)
        );
        rightBtn->setID("right-button");
        
        
        menu->addChild(rightBtn);
        rightBtn->setPositionY(this->getContentHeight() / 2);
        rightBtn->setPositionX(this->m_mainLayer->getContentWidth() - 25.f);
        rightBtn->setRotationY(180.f);
        

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

    
    void onLeft(CCObject * sender);
    void onRight(CCObject * sender);
    void onExit(CCObject * sender);
    void getRatings();
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



