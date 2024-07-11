#pragma once

#include "Geode/binding/GJUserScore.hpp"
#include "Geode/modify/GJUserScore.hpp"
#include "Geode/utils/web.hpp"
#include <string>

using namespace geode::prelude;



struct RatingInfo {
    int m_rating;
    int m_levelID;
    int m_difficulty;
    std::string m_level_name;
    std::string m_creator_name;

};


class RatingsDictionary {
private:
    static RatingsDictionary* instance; // Static pointer to hold the single instance
	std::map<std::string, int> saved_ratings;
	std::vector<RatingInfo> cached_ratings;
	bool cached;
	
    // Private constructor to prevent instantiation
    RatingsDictionary() {
		cached = false;
	}

	int chooseDifficulty(std::string is_demon, std::string raw_diff, std::string demon_diff, std::string is_auto);

	void parseLevel(std::string level, int rating);

public:
    
	std::vector<EventListener<web::WebTask> *> listeners;

	bool isCached() {
		return cached;
	}

    static RatingsDictionary* getInstance() {
        if (!instance) {
            instance = new RatingsDictionary();
        }
        return instance;
    }


    std::vector<RatingInfo>& getCache() {
        return cached_ratings;
    }
	std::map<std::string, int> getSaved() {
		return saved_ratings;
	}

	void cacheAllRatings(std::map<std::string, int> ratings);

	void fetchRating(std::pair<std::string, int> rating, EventListener<web::WebTask> *web_listener);

    void addCachedRating(RatingInfo info) {

		

        cached_ratings.push_back(info);
    }

	void addSavedRating(std::string levelID, int rating) {
		saved_ratings[levelID] = rating;
	}

	void setSavedRatings(std::map<std::string, int> saved) {
		saved_ratings = saved;
	}
	void setCachedRatings(std::vector<RatingInfo> cache) {
		cached_ratings = cache;
	}

};

/*
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
*/