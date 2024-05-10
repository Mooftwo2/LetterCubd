#pragma once

#include "Geode/binding/GJUserScore.hpp"
#include "Geode/modify/GJUserScore.hpp"
using namespace geode::prelude;

class RatingsDictionary {
private:
    static RatingsDictionary* instance; // Static pointer to hold the single instance
    std::map<int, int> ratings; // Regular member variable

    // Private constructor to prevent instantiation
    RatingsDictionary() {}

public:
    // Method to get the instance
    static RatingsDictionary* getInstance() {
        if (!instance) {
            instance = new RatingsDictionary();
        }
        return instance;
    }

    // Method to access the map
    std::map<int, int>& getMap() {
        return ratings;
    }
    void addRating(int levelID, int rating) {
        ratings[levelID] = rating;
    }

    void setRatings(std::map<int, int> myMap) {
        ratings = myMap;
    }
};

template<>
struct matjson::Serialize<std::map<int, int>> {
    static std::map<int, int> from_json(matjson::Value const& value) {
        std::map<int, int> data;
        auto obj = value.as_object();
        for (auto const& entry : obj["ratings"].as_object()) {
            data[std::stoi(entry.first)] = entry.second.as_int();
        }
        return data;
    };

    static matjson::Value to_json(std::map<int, int> const& value) {
        auto obj = matjson::Object();
        for (auto const& pair : value) {
            obj[std::to_string(pair.first)] = pair.second;
        }
        return obj;
    }
};


