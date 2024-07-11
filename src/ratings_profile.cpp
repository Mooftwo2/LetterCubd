#include "ratings_profile.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "ratings_dict.hpp"
#include "rating_cell.hpp"

using namespace geode::prelude;

void RatingProfile::onExit(CCObject * sender) {

    auto account = GJAccountManager::get();
    auto id = account->m_accountID;
    auto alert = OwnProfilePageRatings::create(id, true);
    alert->m_noElasticity = true;
    alert->show();

    this->onClose(sender);

    
}
void RatingProfile::getRatings() {
    auto data = RatingsDictionary::getInstance()->getCache();

    //sort the data here

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

void RatingProfile::sortRatings(std::vector<RatingInfo> *data, std::string filter) {
    CCArrayExt<RatingCell*> objects = scroll->m_contentLayer->getChildren();

    /*
    switch statement of filter

    -dynamically allocate std::vector for objects to sort easier
    */
}
