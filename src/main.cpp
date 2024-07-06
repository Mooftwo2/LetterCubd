#include "Geode/DefaultInclude.hpp"
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/binding/GJAccountManager.hpp"
#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/utils/web.hpp>
#include <cstddef>
#include <string>
#include <vector>
#include "ratings_profile.hpp"
#include "ratings_dict.hpp"
#include "player_profile.hpp"
#include "rating_popup.hpp"

using namespace geode::prelude;

/*
TODO FOR ALPHA RELEASE:

-move web request to main in order to cache the info
-fix profile button placement
-implement pages on ratings profile (10 ratings per page)
-add ability to delete ratings (similar to profile comments)
-add options to sort ratings by various features 


*/

EventListener<web::WebTask> web_listener;

class $modify(LetterCubdMenuLayer, MenuLayer) {
	
	bool init() {
		if (!MenuLayer::init())
			return false;
		
		
		RatingsDictionary* mapInstance = RatingsDictionary::getInstance();
		auto saved = Mod::get()->getSavedValue<std::map<std::string,int>>("ratings");

		/*
		for(const auto& test : saved) {
			log::info("{}", test.first);
			log::info("{}", std::to_string(test.second));
		}
		*/
		

		mapInstance->setSavedRatings(saved);
		Mod::get()->setSavedValue("ratings", saved);

		mapInstance->cacheAllRatings(saved);

		/*
		// Check if we have a value; getValue() always returns a pointer
		m_fields->m_fetchListener.bind([&mapInstance](WebFetchTask::Event* event) {
		// The Task has progressed, finished, or been cancelled! Let's handle that!
			if (std::vector<RatingInfo>* result = event->getValue()) {
			// The Task completed successfully! Do what you need with the value.
				
				mapInstance->setCachedRatings(*result);
				
			}
			else if (int* progress = event->getProgress()) {
				// The progress callback was called.
			}
			// This check is technically unnecessary, since Tasks can only ever have 
			// three possible states, but it's good practice to always check it anyway 
			// in case Task gains more states in the future, or if you get rid of the 
			// progress check for example
			else if (event->isCancelled()) {
				
			}
		
		
		});
			
		if(mapInstance->isCached() == false) {
			m_fields->m_fetchListener.setFilter(fetchRatings(saved));
		}
		*/

		std::vector<RatingInfo> ratings;

		log::info("{}", "fetching");
			web_listener.bind([] (web::WebTask::Event* e) {	
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
		
		for(const auto& rating : saved) {
			auto req = web::WebRequest().userAgent("").bodyString(fmt::format("type=0&secret=Wmfd2893gb7&str={}", rating.first));
			std::string url = "http://www.boomlings.com/database/getGJLevels21.php";
			
			auto task = req.post(url);
			web_listener.setFilter(task);
		}
		
		
		return true;
	}

	void onMyProfile(cocos2d::CCObject *sender) {
		auto account = GJAccountManager::get();
		auto id = account->m_accountID;
		OwnProfilePageRatings::create(id, true)->show();

	}

	void cacheRatings(std::map<std::string, int> saved) {

	}
	

};

class $modify(LevelInfoWithRating, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge))
            return false;
        
        auto menu = CCMenu::create();
        menu->setID("rating-button");
		menu->setAnchorPoint({0.f, 0.f});
		menu->setPosition({0.f, 0.f});
		menu->ignoreAnchorPointForPosition(true);
		

        auto spr = CircleButtonSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
        spr->setScale(0.5f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(LevelInfoWithRating::onClick)
        );
        btn->setID("rating-button");
        btn->setUserObject(level);
    
       	menu->addChild(btn);
        this->addChild(menu);
        auto like_count = this->getChildByID("likes-label");
		btn->setPosition(like_count->getPosition() + CCPoint{(like_count->getContentWidth() * like_count->getScaleX()) + 15.f, 0.f});

        return true;
    }

    void onClick(CCObject* sender) {
        
        auto obj = static_cast<CCNode*>(sender)->getUserObject();
        auto lvl = static_cast<GJGameLevel*>(obj);
        RatingPopup::create(lvl)->show();

        
    }
};

