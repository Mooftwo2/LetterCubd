#include "ratings_profile.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "ratings_dict.hpp"

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
    auto data = RatingsDictionary::getInstance()->getMap();

    for(const auto & rating : data) {
        auto cell = RatingCell::create(rating.first, rating.second);
        scroll->addChild(cell);
    }
}