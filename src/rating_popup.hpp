#pragma once

#include "Geode/Enums.hpp"
#include "Geode/GeneratedPredeclare.hpp"
#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/binding/GJGameLevel.hpp"
#include "Geode/modify/GJUserScore.hpp"
#include "Geode/binding/GJUserScore.hpp"
#include "Geode/cocos/cocoa/CCArray.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/cocos/sprite_nodes/CCSpriteFrame.h"
#include "Geode/loader/Log.hpp"
#include "Geode/ui/Popup.hpp"
#include "ccTypes.h"
#include "ratings_profile.hpp"
#include "ratings_dict.hpp"
#include <array>
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>
#include <vector>

using namespace geode::prelude;

struct ButtonStuff : public CCObject {
    CCMenuItemSpriteExtra * submit_btn;
    std::vector<CCMenuItemSpriteExtra*> star_buttons;
    CCLabelBMFont * rating_text;

    ButtonStuff(CCMenuItemSpriteExtra * sub, std::vector<CCMenuItemSpriteExtra*> stars, CCLabelBMFont *text) : submit_btn(sub), star_buttons(stars), rating_text(text) {
        this->autorelease();
    }
};

class RatingPopup : public geode::Popup<GJGameLevel *> {

float star_rating_float = 0;
int star_rating_int = 0;
int m_levelID = 0;

protected:
    bool setup(GJGameLevel * level) override {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // convenience function provided by Popup 
        // for adding/setting a title to the popup

        this->setTitle("Rate level", "bigFont.fnt", 1.f);
        this->m_title->setColor(ccColor3B {255,255,255});
        
        auto menu = this->m_buttonMenu;
        menu->setID("rating-popup");
        menu->removeChild(this->m_closeBtn, true);

        auto submit_spr = ButtonSprite::create("Submit");
        submit_spr->setColor({166, 166, 166});

        auto submit_btn = CCMenuItemSpriteExtra::create(
            submit_spr,
            this,
            menu_selector(RatingPopup::onSubmit)
            
        );
        submit_btn->setID("submit-button");
        submit_btn->setEnabled(false);
        submit_btn->setUserObject(level);
        

        auto cancel_spr = ButtonSprite::create("Cancel");
        auto cancel_btn = CCMenuItemSpriteExtra::create(
            cancel_spr,
            this,
            menu_selector(RatingPopup::onClose)
        );
        cancel_btn->setID("cancel-button");
        
        menu->addChild(cancel_btn);
        cancel_btn->setPosition((menu->getContentWidth() / 2) - 60.f, 25.f);

        menu->addChild(submit_btn);
        submit_btn->setPosition((menu->getContentWidth() / 2) + 60.f, 25.f);

        //display rating text
        auto rating_text = CCLabelBMFont::create("0.00", "goldFont.fnt");
        rating_text->setID("rating-text");
        rating_text->setPosition({30.f, menu->getContentHeight() - 87.f});
        rating_text->setScale(0.5f);
        menu->addChild(rating_text);
        
        //add star buttons

        auto star_menu = CCMenu::create();
        star_menu->setContentSize({300.f, 80.f});
        star_menu->setPositionX(menu->getPositionX() - menu->getContentWidth() / 2);
        star_menu->setPositionY(menu->getPositionY() - menu->getContentHeight() / 2);
        
        //star_menu->setAnchorPoint({0.0f, 0.5f});
        star_menu->setID("star-menu");
        menu->addChild(star_menu);

        std::vector<CCMenuItemSpriteExtra*> star_buttons;
        
        CCPoint starting_pos = {8.f, 0.f};

        for(int i = 1; i <= 10; ++i) {
            
            CCSprite *star;
            if(i % 2 != 0) {
                star = CCSprite::create("StarLeft_color.png"_spr);
            }else{
                star = CCSprite::create("StarRight_color.png"_spr);
            }
            
            star->setScale(0.8f);
            //star->setColor({166, 166, 166});
            
            auto star_btn = CCMenuItemSpriteExtra::create(
                star,
                this,
                menu_selector(RatingPopup::onStarClick)
            );
            star_btn->setColor({166, 166, 166});
            star_btn->setTag(i);
            star_buttons.push_back(star_btn);
            star_menu->addChild(star_btn);
            
            star_btn->setPositionY((menu->getContentHeight() / 2) + 5.f);
            float gap = star_menu->getContentWidth() / 10;
            if(i % 2 != 0) {
                star_btn->setPositionX(starting_pos.x + ((gap / 2) - 1.f) + ((i - 1) * (gap))); //weird positioning magic
            }
            else{
                star_btn->setPositionX(starting_pos.x + ((i - 1) * gap));
            }

            std::vector<CCMenuItemSpriteExtra*> &ref = star_buttons;
            for(auto star : star_buttons) {
                star->setUserObject(new ButtonStuff(submit_btn, ref, rating_text));
            }
            
        
        }
    
        return true;
    }


    void onStarClick(CCObject* sender) {
        
        auto buttons =static_cast<ButtonStuff*>(
        static_cast<CCNode*>(sender)->getUserObject()
        );

        if(star_rating_float == 0) { 
            auto clickable_spr = ButtonSprite::create("Submit");
            clickable_spr->setColor({255,255,255});
            buttons->submit_btn->setSprite(clickable_spr);
            buttons->submit_btn->updateSprite();
            buttons->submit_btn->setEnabled(true);
        }

        star_rating_float = static_cast<float>(sender->getTag()) / 2.0f;
        star_rating_int = sender->getTag();
        
        //loop through the array of star sprites to change them to black/colored
        //all stars before including the one was clicked get brighter
        //all stars after the one that was clicked get dimmed
        
        auto button_array = buttons->star_buttons;

        _ccColor3B dim = {166, 166, 166};
        _ccColor3B full = {255, 255, 255};


        for(int i = 1; i <= button_array.size(); ++i) {
            auto current_button = static_cast<CCMenuItemSpriteExtra*>(button_array[i - 1]);
            if(i <= star_rating_int) {
                //log::info("full");
                current_button->setColor(full);
            }else{
                //log::info("dim");
                current_button->setColor(dim);

            }

        }
        
        std::string rating_string = std::to_string(star_rating_float);
        buttons->rating_text->setString(rating_string.substr(0,4).c_str());
        //this->setTitle(std::to_string(star_rating_int), "bigFont.fnt", 1.f);

    }
    
    void onSubmit(CCObject* sender) {
        //add star rating to the user's database
        auto obj = static_cast<CCNode*>(sender)->getUserObject();
        auto lvl = static_cast<GJGameLevel*>(obj);

        //log::info("{}", std::to_string(static_cast<int>(lvl->m_difficulty)));

        RatingInfo info = RatingInfo();
        info.m_rating = star_rating_int;
        info.m_levelID = lvl->m_levelID.value();
        info.m_level_name = lvl->m_levelName;
        info.m_creator_name = lvl->m_creatorName;
    
        info.m_difficulty = chooseDiff(lvl->m_stars.value(), lvl->m_demonDifficulty);
        info.m_feature = chooseFeature(lvl->m_featured, lvl->m_isEpic);

        log::info("{}", std::to_string(info.m_feature));

        auto ratings_data = RatingsDictionary::getInstance();
        ratings_data->addCachedRating(info);
        ratings_data->addSavedRating(std::to_string(info.m_levelID), info.m_rating);
        
        Mod::get()->setSavedValue("ratings", ratings_data->getSaved());
        //log::info("{}", std::to_string(value));
        this->onClose(sender);
    }

    int chooseFeature(int featured, int epic) {
        if(epic == 3) {
            return 5;
        }else if (epic == 2) {
            return 4;
        }else if (epic == 1) {
            return 3;
        }else if (epic == 0 && featured > 0) {
            return 2;
        }else {
            return 1;
        }
    }

    int chooseDiff(int stars, int demon) {
    
        if(stars == 0) {
            //do it for unrated difficulties later

            return -1;
        }
        else if(stars == 1) {
            return 0;

        }
        else if(stars == 2) {
            return 1;
        }
        else if (stars == 3) {
            return 2;
        }
        else if (stars == 4 || stars == 5) {
            return 3;
        }
        else if (stars == 6 || stars == 7) {
            return 4;
        }
        else if (stars == 8 || stars == 9) {
            return 5;
        }
        else if (stars == 10) {
            if(demon == 0) {
                return 6;
            }
            else if (demon == 3) {
                return 7;
            }
            else if (demon == 4) {
                return 8;
            }
            else if (demon == 5) {
                return 9;
            }
            else if (demon == 6) {
                return 10;
            }
        }
        
        return -1;
    }

public:
    static RatingPopup* create(GJGameLevel * level) {
        auto ret = new RatingPopup();
        if (ret && ret->initAnchored(300.f, 140.f, level)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};