#include "Geode/ui/Popup.hpp"

using namespace geode::prelude;

class RatingPopup : public geode::Popup<std::string const&> {
protected:
    bool setup(std::string const& value) override {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // convenience function provided by Popup 
        // for adding/setting a title to the popup
        this->setTitle("Rate level");

        //auto label = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
        //label->setPosition(winSize / 2);

        //we add the buttons here

        //this->addChild(label);

        return true;
    }

public:
    static RatingPopup* create(std::string const& text) {
        auto ret = new RatingPopup();
        if (ret && ret->initAnchored(300.f, 150.f, text)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};