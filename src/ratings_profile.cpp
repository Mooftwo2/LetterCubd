#include "ratings_profile.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "ratings_dict.hpp"
#include "rating_cell.hpp"
#include <cassert>
#include <string>

using namespace geode::prelude;

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
    auto data = RatingsDictionary::getInstance()->getCache();
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
    


    //GETTING THE RATING CELLS
    
    int basePosY = this->getContentHeight();
    for(const auto & rating : data) {
        auto cell = RatingCell::create(rating); 
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

void RatingProfile::setupPage(int pageNum) {


    log::info("{}", std::to_string(pageNum));
    auto leftBtn = static_cast<CCMenuItemSpriteExtra *>(this->m_buttonMenu->getChildByID("left-button"));

    if(pageNum == 0) {
        leftBtn->setVisible(false);
        leftBtn->setEnabled(false);
    }else {
        leftBtn->setVisible(true);
        leftBtn->setEnabled(true);
    }
    
}

void RatingProfile::sortRatings(std::vector<RatingInfo> *data, std::string filter) {
    CCArrayExt<RatingCell*> objects = scroll->m_contentLayer->getChildren();

    /*
    switch statement of filter

    -dynamically allocate std::vector for objects to sort easier
    */
}
