#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/ui/Popup.hpp"

using namespace geode::prelude;

class RatingPopup : public geode::Popup<std::string const&> {
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

        return true;
    }


    void onStarClick(CCObject* sender) {

    }
    
    void onSubmit(CCObject* sender) {
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