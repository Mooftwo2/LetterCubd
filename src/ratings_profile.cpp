#include "ratings_profile.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/touch_dispatcher/CCTouchDispatcher.h"
#include "Geode/loader/Log.hpp"
#include "ratings_dict.hpp"
#include "rating_cell.hpp"
#include <cassert>
#include <string>

using namespace geode::prelude;

 const int elementsPerPage = 10;

void RatingProfile::onSort(CCObject * sender) {
    
    SortPopup::create()->show();
}

void RatingProfile::onExit(CCObject * sender) {

    auto account = GJAccountManager::get();
    auto id = account->m_accountID;
    auto alert = OwnProfilePageRatings::create(id, true);
    alert->m_noElasticity = true;
    alert->show();

    this->onClose(sender);
}

void RatingProfile::onLeft(CCObject * sender) {

    --pageNum;
    assert(pageNum >= 0); 
    setupPage(pageNum);
}

void RatingProfile::onRight(CCObject * sender) {
    ++pageNum;
    setupPage(pageNum);
    
}

void RatingProfile::setupPageInitial() {
    
    auto menu = this->m_buttonMenu;

    auto leftBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(RatingProfile::onLeft)
    );
    leftBtn->setID("left-button");
    menu->addChild(leftBtn);
    leftBtn->setPositionY(this->getContentHeight() / 2);
    leftBtn->setPositionX(this->getPositionX() + 25.f);
    
    leftBtn->setVisible(false);
    leftBtn->setEnabled(false);

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
    
    setupPage(0);

    
        
}

void RatingProfile::setupPage(int pageNum) {

    auto data = RatingsDictionary::getInstance()->getCache();

    log::info("{}", std::to_string(pageNum));

    auto leftBtn = static_cast<CCMenuItemSpriteExtra *>(this->m_buttonMenu->getChildByID("left-button"));
    auto rightBtn = static_cast<CCMenuItemSpriteExtra *>(this->m_buttonMenu->getChildByID("right-button"));

    if(pageNum == 0) {
        leftBtn->setVisible(false);
        leftBtn->setEnabled(false);
    }else {
        leftBtn->setVisible(true);
        leftBtn->setEnabled(true);
    }
    if(pageNum == data.size() / 10) {
        rightBtn->setVisible(false);
        rightBtn->setEnabled(false);
    }else {
        rightBtn->setVisible(true);
        rightBtn->setEnabled(true);
    }
    
    scroll->m_contentLayer->removeAllChildrenWithCleanup(true); //check for memory leak

    size_t startIndex = pageNum * elementsPerPage;
    size_t endIndex = startIndex + elementsPerPage;

    assert(startIndex <= data.size());

    endIndex = std::min(endIndex, data.size());

    int basePosY = this->getContentHeight();

    // Process the determined number of elements
    for (size_t i = startIndex; i < endIndex; ++i) {
    int basePosY = this->getContentHeight();

        auto cell = RatingCell::create(data[i]); 
        cell->setPositionY(basePosY);
        scroll->m_contentLayer->addChild(cell);
        scroll->m_contentLayer->setAnchorPoint(ccp(0,1));
    }
    float height = std::max<float>(scroll->getContentSize().height, 65 * scroll->m_contentLayer->getChildrenCount());

    scroll->m_contentLayer->setContentSize(ccp(scroll->m_contentLayer->getContentSize().width, height));
    CCArrayExt<RatingCell*> objects = scroll->m_contentLayer->getChildren();

    int i = 0;
    for (auto* obj : objects) {
        i++;
        obj->setPositionY(height - (65 * i));
    }
    scroll->moveToTop();


}

void RatingProfile::sortRatings(std::vector<RatingInfo> *data, std::string filter) {
    CCArrayExt<RatingCell*> objects = scroll->m_contentLayer->getChildren();

    /*
    switch statement of filter

    -dynamically allocate std::vector for objects to sort easier
    */
}

void SortPopup::onSortSelect(CCObject * sender) {

    auto filter = sender->getTag();

    log::info("{}", std::to_string(filter));

    auto data = RatingsDictionary::getInstance()->getCache();

    switch(filter) {

        case 0: //score
            std::sort(data.begin(), data.end(), [](const RatingInfo& a, const RatingInfo& b) {
            return a.m_rating < b.m_rating;
            });
            break;
        case 1: //level ID
            std::sort(data.begin(), data.end(), [](const RatingInfo& a, const RatingInfo& b) {
            return a.m_levelID < b.m_levelID;
            });
            break;
        case 2: //difficulty
            std::sort(data.begin(), data.end(), [](const RatingInfo& a, const RatingInfo& b) {
            return a.m_difficulty < b.m_difficulty;
            });
            break;
        case 3: //feature
            std::sort(data.begin(), data.end(), [](const RatingInfo& a, const RatingInfo& b) {
            return a.m_feature < b.m_feature;
            });
            break;
        case 4: //level name
            std::sort(data.begin(), data.end(), [](const RatingInfo& a, const RatingInfo& b) {
            return a.m_level_name < b.m_level_name;
            });
            break;
        case 5: //creator name
            std::sort(data.begin(), data.end(), [](const RatingInfo& a, const RatingInfo& b) {
            return a.m_creator_name < b.m_creator_name;
            });
            break;
        default:
            break;

    }

    RatingsDictionary::getInstance()->setCachedRatings(data);

    //find some way to call setupPageInitial()
    

    this->onClose(sender);
}
