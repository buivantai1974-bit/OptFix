#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/CCSpriteFrameCache.hpp>

using namespace geode::prelude;

static bool s_purgedThisLevel = false;

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

        s_purgedThisLevel = false;

        if (Mod::get()->getSettingValue<bool>("purge-sprites")) {
            cocos2d::CCSpriteFrameCache::get()->removeUnusedSpriteFrames();
        }

        return true;
    }

    void update(float dt) {
        if (!s_purgedThisLevel && Mod::get()->getSettingValue<bool>("purge-sprites")) {
            cocos2d::CCSpriteFrameCache::get()->removeUnusedSpriteFrames();
            s_purgedThisLevel = true;
        }

        PlayLayer::update(dt);
    }
};

class $modify(OptFixSpriteCache, cocos2d::CCSpriteFrameCache) {
    void addSpriteFramesWithFile(const char* plist) {
        if (Mod::get()->getSettingValue<bool>("disable-glow")) {
            std::string p = plist ? plist : "";
            if (p.find("glow") != std::string::npos || p.find("Glow") != std::string::npos) {
                return;
            }
        }
        cocos2d::CCSpriteFrameCache::addSpriteFramesWithFile(plist);
    }
};

$execute {
    log::info("OptFix loaded | fps-cap={} purge={} no-glow={}",
        Mod::get()->getSettingValue<int>("fps-cap"),
        Mod::get()->getSettingValue<bool>("purge-sprites"),
        Mod::get()->getSettingValue<bool>("disable-glow"));
}
