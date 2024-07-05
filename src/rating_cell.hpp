
#include "Geode/binding/TableViewCell.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h"
#include "Geode/cocos/sprite_nodes/CCSprite.h"
#include "Geode/modify/Modify.hpp"
#include "Geode/ui/ListView.hpp"
#include <Geode/utils/web.hpp>
#include <string>

using namespace geode::prelude;


struct RatingInfo {
    int m_rating;
    int m_levelID;
    int m_difficulty;
    int m_demon_difficulty;
    std::string m_level_name;
    std::string m_creator_name;

};


class RatingCell : public CCLayerColor {

CCSprite * diff_spr;
CCSprite * star_sprite;
CCLabelBMFont * level_text;
CCLabelBMFont * creator_text;
RatingInfo m_info;

EventListener<web::WebTask> m_listener;

    bool init(std::string levelID, int rating) {
        if(!CCLayerColor::init()) {return false;}
        m_info.m_rating = rating;
        
        this->setContentSize(ccp(350, 60));
        this->setOpacity(50);
        this->setAnchorPoint(ccp(0, 0));
    
        //web fetch
    
        m_listener.bind([this] (web::WebTask::Event* e) {
            
            if (web::WebResponse* value = e->getValue()) {
                // The request finished!
                auto str = value->string().unwrap();

                log::info("{}", str);

            } else if (web::WebProgress* progress = e->getProgress()) {
                // The request is still in progress...
                //log::info("{}", "progress");


            } else if (e->isCancelled()) {
                // Our request was cancelled
                //log::info("{}", "fail");
                
            }
        });

        auto req = web::WebRequest().userAgent("").bodyString(fmt::format("type=0&secret=Wmfd2893gb7&str={}", levelID));
        std::string url = "http://www.boomlings.com/database/getGJLevels21.php";
        
        auto task = req.post(url);
        m_listener.setFilter(task);
        
        
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

    void chooseDifficultySprite(std::string is_demon, std::string raw_diff, std::string demon_diff, std::string is_auto) {
        //yandere dev level coding :)
        
        if(is_auto == "1") {
            diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_auto_btn_001.png");
            return;
        }
        if(is_demon == "1") {
            if(demon_diff == "3") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_07_btn_001.png");
            }else if(demon_diff == "4") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_08_btn_001.png");
            }else if(demon_diff == "0") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_06_btn_001.png");
            }else if (demon_diff == "5") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_09_btn_001.png");
            }else if (demon_diff == "6") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_10_btn_001.png");
            }
        }
        else{
            if(raw_diff == "0") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_00_btn_001.png");
            }else if(raw_diff == "10") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_01_btn_001.png");
            }else if(raw_diff == "20") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_02_btn_001.png");
            }else if(raw_diff == "30") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_03_btn_001.png");
            }else if(raw_diff == "40") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_04_btn_001.png");
            }else if (raw_diff == "50") {
                diff_spr = CCSprite::createWithSpriteFrameName("diffIcon_05_btn_001.png");
            }
            
        }
        



    }

    void parseLevel(std::string level) {
        std::unordered_map<std::string, std::string> result;
        std::vector<std::string> tokens;
        std::stringstream ss(level);
        std::string token;

        //extract the creator's name from the query
        std::string creator_substring = level.substr(level.find("#"));
        size_t firstColon = creator_substring.find(':');
        size_t secondColon = creator_substring.find(':', firstColon + 1);
        if (firstColon != std::string::npos && secondColon != std::string::npos) {
            m_info.m_creator_name = creator_substring.substr(firstColon + 1, secondColon - firstColon - 1);
        }

        // Split the string by ':'
        while (std::getline(ss, token, ':')) {
            tokens.push_back(token);
        }

        // Iterate through the tokens and populate the map
        for (size_t i = 0; i < tokens.size(); i += 2) {
            if (i + 1 < tokens.size()) {
                result[tokens[i]] = tokens[i + 1];
            }
        }
        
        //updating info from the map
        m_info.m_level_name = result.find("2")->second;
        
        log::info("{}", result.find("17")->second);
        
        chooseDifficultySprite(result.find("17")->second, result.find("9")->second, result.find("43")->second, result.find("25")->second);


        onGetLevelFinished();
        
    }


   
    void onGetLevelFinished() {
        //generate the UI Content
        
        //diff_spr = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png"); //REPLACE WITH DIFFICULTY FACES
        diff_spr->setPositionY(this->getContentHeight()/2);
        diff_spr->setPositionX(diff_spr->getPositionX() + 25.f);
        this->addChild(diff_spr);

        //auto name_str = (m_level_name).c_str();
        //log::info("{}", m_level_name);
        level_text = CCLabelBMFont::create(m_info.m_level_name.c_str(), "goldFont.fnt");
        creator_text = CCLabelBMFont::create(m_info.m_creator_name.c_str(), "goldFont.fnt"); //PLACEHOLDER TEXT

        
        chooseStarSprite(m_info.m_rating);
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
    /*
    RatingInfo getRatingInfo() {
        return this->m_info;
    }
    */
};