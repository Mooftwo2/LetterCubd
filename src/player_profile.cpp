#include "player_profile.hpp"

using namespace geode::prelude;

void OwnProfilePageRatings::onRatingsClick(CCObject * sender) {
    auto alert = RatingProfile::create();
    alert->m_noElasticity = true;
    alert->show();
    this->onClose(sender);

}