#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

class $modify(OptFixDirector, cocos2d::CCDirector) {
    void setAnimationInterval(double interval) {
        int cap = Mod::get()->getSettingValue<int>("fps-cap");
        if (cap > 0) {
            interval = 1.0 / static_cast<double>(cap);
        }
        cocos2d::CCDirector::setAnimationInterval(interval);
    }
};

class $modify(OptFixPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        
        if (Mod::get()->getSettingValue<bool>("purge-sprites")) {
            cocos2d::CCSpriteFrameCache::get()->removeUnusedSpriteFrames();
        }
        return true;
    }
};
