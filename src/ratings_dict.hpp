#pragma once

#include "Geode/binding/GJUserScore.hpp"
#include "Geode/modify/GJUserScore.hpp"
using namespace geode::prelude;

class $modify(UserScoreRatings, GJUserScore) {
    struct Fields {
        std::map<int, int> m_ratings;
    };

public:
    void addRating(int levelID, int rating) {
        m_fields->m_ratings[levelID] = rating;    
    }

};