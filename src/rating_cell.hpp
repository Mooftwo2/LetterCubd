
#include "Geode/Enums.hpp"
#include "Geode/binding/TableViewCell.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/modify/Modify.hpp"
#include "Geode/ui/ListView.hpp"
#include <Geode/utils/web.hpp>
#include "ratings_dict.hpp"
#include <string>

using namespace geode::prelude;



class RatingCell : public CCLayerColor {

CCSprite * diff_spr;
CCSprite * star_sprite;
CCLabelBMFont * level_text;
CCLabelBMFont * creator_text;
RatingInfo m_info;

    bool init(RatingInfo info) {
        if(!CCLayerColor::init()) {return false;}
        m_info = info;
        
        this->setContentSize(ccp(350, 60));
        this->setOpacity(50);
        this->setAnchorPoint(ccp(0, 0));

        //generate the UI Content
        chooseStarSprite(info.m_rating);
        chooseDifficultySprite(info.m_difficulty);

        diff_spr->setPositionY(this->getContentHeight()/2);
        diff_spr->setPositionX(diff_spr->getPositionX() + 25.f);
        this->addChild(diff_spr);

        //auto name_str = (m_level_name).c_str();
        //log::info("{}", m_level_name);
        level_text = CCLabelBMFont::create(info.m_level_name.c_str(), "goldFont.fnt");
        creator_text = CCLabelBMFont::create(info.m_creator_name.c_str(), "goldFont.fnt"); //PLACEHOLDER TEXT

        star_sprite->setScale(0.5f);
        star_sprite->setPositionX(this->getContentWidth() - 65.f);
        star_sprite->setPositionY(diff_spr->getPositionY());
        this->addChild(star_sprite);
        
        level_text->limitLabelWidth(150.f, 1.f, 0.5f);
        level_text->setPositionY(diff_spr->getPositionY() + 20.f);
        level_text->setPositionX(diff_spr->getPositionX() + 100.f);

        creator_text->limitLabelWidth(150.f, 1.f, 0.5f);
        creator_text->setPositionX(level_text->getPositionX());
        creator_text->setPositionY(level_text->getPositionY() - 30.f);
        creator_text->setScale(0.8f);

        this->addChild(level_text);
        this->addChild(creator_text);
        
        
        return true;
    }
    
    void chooseStarSprite(int rating) {
        //this is awful but idc lololololol
        switch (rating) {
            case 1:
                star_sprite = CCSprite::createWithSpriteFrameName("half star.png"_spr);
                break;
            case 2:
                star_sprite = CCSprite::createWithSpriteFrameName("1 star.png"_spr);
                break;
            case 3:
                star_sprite = CCSprite::createWithSpriteFrameName("1.5 stars.png"_spr);
                break;  
            case 4:
                star_sprite = CCSprite::createWithSpriteFrameName("2 star.png"_spr);
                break; 
            case 5:
                star_sprite = CCSprite::createWithSpriteFrameName("2.5 star.png"_spr);
                break; 
            case 6:
                star_sprite = CCSprite::createWithSpriteFrameName("3 star.png"_spr);
                break; 
            case 7:
                star_sprite = CCSprite::createWithSpriteFrameName("3.5 star.png"_spr);
                break; 
            case 8:
                star_sprite = CCSprite::createWithSpriteFrameName("4 star.png"_spr);
                break; 
            case 9:
                star_sprite = CCSprite::createWithSpriteFrameName("4.5 star.png"_spr);
                break; 
            case 10:
                star_sprite = CCSprite::createWithSpriteFrameName("5 star.png"_spr);
                break; 
            default:
                log::info("{}", "why am i here");
                break;
        }
    }

    void chooseDifficultySprite(int difficulty) {
        //yandere dev level coding :)
        
        switch(difficulty) {
            case -1:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_00_btn_001.png");
                break;
            case 0:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_auto_btn_001.png");
                break;
            case 1:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_01_btn_001.png");
                break;
            case 2:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_02_btn_001.png");
                break;
            case 3:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_03_btn_001.png");
                break;
            case 4:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_04_btn_001.png");
                break;
            case 5:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_05_btn_001.png");
                break;
            case 6:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_06_btn_001.png");
                break;
            case 7:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_07_btn_001.png");
                break;
            case 8:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_08_btn_001.png"); 
                break;
            case 9:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_09_btn_001.png");
                break;
            case 10:
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_10_btn_001.png");
                break;
            default:
                break;

        }
       
    }

   

public:
    static RatingCell* create(RatingInfo info) {
        RatingCell* pRet = new RatingCell();
        if (pRet && pRet->init(info)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            return nullptr;
        }
    }
    /*
    RatingInfo getRatingInfo() {
        return this->m_info;
    }
    */
};