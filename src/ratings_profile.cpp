#include "ratings_profile.hpp"
#include "Geode/cocos/cocoa/CCObject.h"

using namespace geode::prelude;

void RatingProfile::onExit(CCObject * sender) {

    auto account = GJAccountManager::get();
    auto id = account->m_accountID;
    auto alert = OwnProfilePageRatings::create(id, true);
    alert->m_noElasticity = true;
    alert->show();

    this->onClose(sender);

    
}