#pragma once

#include "Geode/binding/GJUserScore.hpp"
#include "Geode/modify/GJUserScore.hpp"
using namespace geode::prelude;

class RatingsDictionary {
private:
    static RatingsDictionary* instance; // Static pointer to hold the single instance
    std::map<std::string, int> ratings; // Regular member variable

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
    std::map<std::string, int>& getMap() {
        return ratings;
    }
    void addRating(std::string levelID, int rating) {
        ratings[levelID] = rating;
    }

    void setRatings(std::map<std::string, int> myMap) {
        ratings = myMap;
    }
};

template <class T>
	struct matjson::Serialize<std::map<std::string, T>> {
		static std::map<std::string, T> from_json(Value const& value)
			requires requires(Value const& value) {
				value.template as<std::decay_t<T>>();
			}
		{
			std::map<std::string, T> res;
			auto obj = value.as_object();
			for (auto& [k, v] : obj) {
				res.insert({ k, v.template as<std::decay_t<T>>() });
			}
			return res;
		}

		static Value to_json(std::map<std::string, T> const& value)
			requires requires(T const& value) {
				Value(value);
			}
		{
			Object res;
			for (auto& [k, v] : value) {
				res[k] = (Value(v));
			}
			return res;
		}

		static bool is_json(Value const& value) {
			// TODO: this is intentionally lazy..
			return value.is_object();
		}
	};

