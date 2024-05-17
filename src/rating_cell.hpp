
#include "Geode/binding/TableViewCell.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/modify/Modify.hpp"
#include "Geode/ui/ListView.hpp"
#include <string>

using namespace geode::prelude;

class RatingCell : public CCLayerColor {

    bool init(std::string levelID, int rating) {
        if(!CCLayerColor::init()) {return false;}

        this->setContentSize(ccp(350, 60));
        this->setOpacity(50);
        this->setAnchorPoint(ccp(0, 0));

        //web fetch
        

        //generate the UI Content
        auto diff_spr = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png"); //REPLACE WITH DIFFICULTY FACES
        diff_spr->setPositionY(this->getContentHeight()/2);
        diff_spr->setPositionX(diff_spr->getPositionX() + 25.f);
        this->addChild(diff_spr);

        auto level_text = CCLabelBMFont::create("Level Name", "goldFont.fnt");
        auto creator_text = CCLabelBMFont::create("Creator", "goldFont.fnt"); //PLACEHOLDER TEXT
        
        level_text->setPositionY(diff_spr->getPositionY() + 20.f);
        level_text->setPositionX(diff_spr->getPositionX() + 100.f);

        creator_text->setPositionX(level_text->getPositionX());
        creator_text->setPositionY(level_text->getPositionY() - 30.f);
        creator_text->setScale(0.8f);

        this->addChild(level_text);
        this->addChild(creator_text);

        return true;
    }

    void fetchLevel(std::string levelID) {

    }


public:
    static RatingCell* create(std::string levelID, int rating) {
        RatingCell* pRet = new RatingCell();
        if (pRet && pRet->init(levelID, rating)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            return nullptr;
        }
    }
};