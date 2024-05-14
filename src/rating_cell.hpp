
#include "Geode/binding/TableViewCell.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h"
#include "Geode/modify/Modify.hpp"
#include "Geode/ui/ListView.hpp"
#include <string>
using namespace geode::prelude;

class RatingCell : public CCLayerColor {
    
    bool init(std::string levelID, int rating) {
        if(!CCLayerColor::init()) {return false;}

        //web fetch
        log::info("{}", levelID);
        log::info("{}", std::to_string(rating));

        //generate the UI Content

        
        return true;
    }


public:
    static RatingCell* create(std::string levelID, int rating) {
        RatingCell* pRet = new RatingCell();
        if (pRet && pRet->init(levelID, rating)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            return nullptr;
        }
    }
};