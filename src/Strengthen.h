#pragma once

#include "MonsterList.h"
#include "ll/api/event/ListenerBase.h"

#include <ll/api/plugin/NativePlugin.h>


Config mConfig;

namespace Strengthen {

class Strengthen {
    Strengthen();

public:
    Strengthen(Strengthen&&)                 = delete;
    Strengthen(const Strengthen&)            = delete;
    Strengthen& operator=(Strengthen&&)      = delete;
    Strengthen& operator=(const Strengthen&) = delete;

    static Strengthen& getInstance();

    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const;

    /// @return True if the plugin is loaded successfully.
    bool load(ll::plugin::NativePlugin&);

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

private:
    ll::plugin::NativePlugin* mSelf{};
    ll::event::ListenerPtr    mMobSpawned;
   
};

} // namespace Strengthen

