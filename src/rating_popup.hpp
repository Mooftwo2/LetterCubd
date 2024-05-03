#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/cocos/cocoa/CCArray.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/cocos/sprite_nodes/CCSpriteFrame.h"
#include "Geode/ui/Popup.hpp"
#include <array>
#include <string>

using namespace geode::prelude;

class RatingPopup : public geode::Popup<std::string const&> {

float star_rating = 0;

protected:
    bool setup(std::string const& value) override {
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        // convenience function provided by Popup 
        // for adding/setting a title to the popup
        this->setTitle("Rate level", "bigFont.fnt", 1.f);
        this->m_title->setColor(ccColor3B {255,255,255});
        
        auto menu = this->m_buttonMenu;
        menu->setID("rating-popup");
        menu->removeChild(this->m_closeBtn, true);

        auto submit_spr = ButtonSprite::create("Submit");
        
        auto submit_btn = CCMenuItemSpriteExtra::create(
            submit_spr,
            this,
            menu_selector(RatingPopup::onSubmit)
        );
        submit_btn->setID("submit-button");

        auto cancel_spr = ButtonSprite::create("Cancel");
        auto cancel_btn = CCMenuItemSpriteExtra::create(
            cancel_spr,
            this,
            menu_selector(RatingPopup::onClose)
        );
        cancel_btn->setID("cancel-button");
       
        menu->addChild(cancel_btn);
        cancel_btn->setPosition((menu->getContentWidth() / 2) - 60.f, 30.f);

        menu->addChild(submit_btn);
        submit_btn->setPosition((menu->getContentWidth() / 2) + 60.f, 30.f);

        
        //add star buttons
        CCArray *star_buttons;
        star_buttons = CCArray::createWithCapacity(10);

        
        CCPoint starting_pos = {20.f, 20.f};

        for(int i = 1; i <= 10; ++i) {
            auto star = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
            auto star_btn = CCMenuItemSpriteExtra::create(
                star,
                this,
                menu_selector(RatingPopup::onStarClick)
            );
            star_btn->setTag(i);
            star_btn->setUserObject(star_buttons);
            star_buttons->addObject(star_btn);

            menu->addChild(star_btn);
            star_btn->setPositionX(starting_pos.x + (i * 10.f));
        }
        

        return true;
    }


    void onStarClick(CCObject* sender) {

        star_rating = static_cast<float>(sender->getTag()) / 2.0f;
        int star_rating_int = sender->getTag();
        
        std::string test = std::to_string(std::round(star_rating * 100) / 100);

        this->setTitle(test, "bigFont.fnt", 1.f);
        //loop through the array of star sprites to change them to black/colored



    }
    
    void onSubmit(CCObject* sender) {
        //add star rating to the user's database
        this->setTitle("test", "bigFont.fnt", 1.f);
        this->onClose(sender);
    }

public:
    static RatingPopup* create(std::string const& text) {
        auto ret = new RatingPopup();
        if (ret && ret->initAnchored(300.f, 140.f, text)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};