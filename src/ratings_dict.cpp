#include "ratings_dict.hpp"
#include "Geode/Enums.hpp"
#include <string>

RatingsDictionary* RatingsDictionary::instance = nullptr;

void RatingsDictionary::cacheAllRatings(std::map<std::string, int> ratings) {

    for(int i = 0; i < ratings.size(); ++i) {
        listeners.push_back(new EventListener<web::WebTask>);
    }
    //log::info("{}", listeners.size());

    int counter = 0;
    for(const auto& rating : ratings) {

        fetchRating(rating, listeners[counter]);
        ++counter;
    }    
    cached = true;
}
void RatingsDictionary::fetchRating(std::pair<std::string, int> rating, EventListener<web::WebTask> *web_listener) {

    //log::info("{}", rating.first);
    web_listener->bind([this, rating] (web::WebTask::Event* e) {	
        if (web::WebResponse* value = e->getValue()) {
            // The request finished!
            auto str = value->string().unwrap();
            //log::info("{}", str);
            parseLevel(str, rating.second);
            

        } else if (web::WebProgress* progress = e->getProgress()) {
            // The request is still in progress...
            //log::info("{}", "progress");


        } else if (e->isCancelled()) {
            // Our request was cancelled
            //log::info("{}", "fail");
            
        }
    });


    auto req = web::WebRequest().userAgent("").bodyString(fmt::format("type=0&secret=Wmfd2893gb7&str={}", rating.first));
    std::string url = "http://www.boomlings.com/database/getGJLevels21.php";
    auto task = req.post(url);
    web_listener->setFilter(task);

}

void RatingsDictionary::parseLevel(std::string level, int rating) {
    std::unordered_map<std::string, std::string> result;
    std::vector<std::string> tokens;
    std::stringstream ss(level);
    std::string token;

    RatingInfo item;
    item.m_rating = rating;

    //extract the creator's name from the query
    std::string creator_substring = level.substr(level.find("#"));
    size_t firstColon = creator_substring.find(':');
    size_t secondColon = creator_substring.find(':', firstColon + 1);
    if (firstColon != std::string::npos && secondColon != std::string::npos) {
        item.m_creator_name = creator_substring.substr(firstColon + 1, secondColon - firstColon - 1);
    }

    // Split the string by ':'
    while (std::getline(ss, token, ':')) {
        tokens.push_back(token);
    }

    // Iterate through the tokens and populate the map
    for (size_t i = 0; i < tokens.size(); i += 2) {
        if (i + 1 < tokens.size()) {
            result[tokens[i]] = tokens[i + 1];
        }
    }
    
    //updating info from the map
    item.m_level_name = result.find("2")->second;
    item.m_levelID = std::stoi(result.find("1")->second);
    item.m_difficulty = chooseDifficulty(result.find("17")->second, result.find("9")->second, result.find("43")->second, result.find("25")->second);
    
    addCachedRating(item);
}

int RatingsDictionary::chooseDifficulty(std::string is_demon, std::string raw_diff, std::string demon_diff, std::string is_auto) {
    GJDifficulty test;
    if(is_auto == "1") {
        return 0;
    }
    if(is_demon == "1") {
        if(demon_diff == "3") {
            return 7;
        }else if(demon_diff == "4") {
            return 8;
        }else if(demon_diff == "0") {
            return 6;
        }else if (demon_diff == "5") {
            return 9;
        }else if (demon_diff == "6") {
            return 10;
        }
    }
    else{
        if(raw_diff == "0") {
            return -1;
        }else if(raw_diff == "10") {
            return 1;
        }else if(raw_diff == "20") {
            return 2;
        }else if(raw_diff == "30") {
            return 3;
        }else if(raw_diff == "40") {
            return 4;
        }else if (raw_diff == "50") {
            return 5;
        }
        
    }

    return -2;
}