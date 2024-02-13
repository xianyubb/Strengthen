#include "Strengthen.h"

#include "ll/api/Config.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/ListenerBase.h"
#include "ll/api/event/world/SpawnMobEvent.h"
#include "mc/world/attribute/AttributeInstance.h"
#include "mc/world/attribute/SharedAttributes.h"

#include <ll/api/plugin/NativePlugin.h>
#include <memory>


void setHealth(optional_ref<Mob> &Mob, MonsterList MobType, Config& config) {
    auto mob = getMob(MobType, config);
    Mob->getMutableAttribute(SharedAttributes::HEALTH)->setMaxValue(mob.health);
    Mob->getMutableAttribute(SharedAttributes::HEALTH)->setCurrentValue(mob.health);
}

void setAttack(optional_ref<Mob> &Mob, MonsterList MobType, Config& config) {
    auto mob = getMob(MobType, config);
    Mob->getMutableAttribute(SharedAttributes::ATTACK_DAMAGE)->setMaxValue(mob.attack);
    Mob->getMutableAttribute(SharedAttributes::ATTACK_DAMAGE)->setCurrentValue(mob.attack);
}

void setSpeed(optional_ref<Mob> &Mob, MonsterList MobType, Config& config, const std::string& speedType) {
    if (speedType == "speed") {
        auto mob = getMob(MobType, config);
        Mob->getMutableAttribute(SharedAttributes::MOVEMENT_SPEED)->setMaxValue(mob.speed.speed);
        Mob->getMutableAttribute(SharedAttributes::MOVEMENT_SPEED)->setCurrentValue(mob.speed.speed);
    } else if (speedType == "water_speed") {
        auto mob = getMob(MobType, config);
        Mob->getMutableAttribute(SharedAttributes::UNDERWATER_MOVEMENT_SPEED)->setMaxValue(mob.speed.water_speed);
        Mob->getMutableAttribute(SharedAttributes::UNDERWATER_MOVEMENT_SPEED)->setCurrentValue(mob.speed.water_speed);
    } else if (speedType == "lava_speed") {
        auto mob = getMob(MobType, config);
        Mob->getMutableAttribute(SharedAttributes::LAVA_MOVEMENT_SPEED)->setMaxValue(mob.speed.lava_speed);
        Mob->getMutableAttribute(SharedAttributes::LAVA_MOVEMENT_SPEED)->setCurrentValue(mob.speed.lava_speed);
    }
}

void setFllowRange(optional_ref<Mob> &Mob, MonsterList MobType, Config& config) {
    auto mob = getMob(MobType, config);
    Mob->getMutableAttribute(SharedAttributes::FOLLOW_RANGE)->setMaxValue(mob.follow_range);
    Mob->getMutableAttribute(SharedAttributes::FOLLOW_RANGE)->setCurrentValue(mob.follow_range);
}

void setJumpStrength(optional_ref<Mob> &Mob, MonsterList MobType, Config& config) {
    auto mob = getMob(MobType, config);
    Mob->getMutableAttribute(SharedAttributes::JUMP_STRENGTH)->setMaxValue(mob.jump_strength);
    Mob->getMutableAttribute(SharedAttributes::JUMP_STRENGTH)->setCurrentValue(mob.jump_strength);
}

void setKnockbackResistance(optional_ref<Mob> &Mob, MonsterList MobType, Config& config) {
    auto mob = getMob(MobType, config);
    Mob->getMutableAttribute(SharedAttributes::KNOCKBACK_RESISTANCE)->setMaxValue(mob.knockback_resistance);
    Mob->getMutableAttribute(SharedAttributes::KNOCKBACK_RESISTANCE)->setCurrentValue(mob.knockback_resistance);
}

void setLuck(optional_ref<Mob> &Mob, MonsterList MobType, Config& config) {
    auto mob = getMob(MobType, config);
    Mob->getMutableAttribute(SharedAttributes::LUCK)->setMaxValue(mob.luck);
    Mob->getMutableAttribute(SharedAttributes::LUCK)->setCurrentValue(mob.luck);
}

void setAttribute(optional_ref<Mob> &Mob, Config& config, MonsterList MobType) {
    auto mob = getMob(MobType, config);
    if (bool(mob.attack)) {
        setHealth(Mob, MobType, config);
    }
    if (bool(mob.health)) {
        setAttack(Mob, MobType, config);
    }
    if (bool(mob.speed.speed)) {
        setSpeed(Mob, MobType, config, "speed");
    }
    if (bool(mob.jump_strength)) {
        setJumpStrength(Mob, MobType, config);
    }
    if (bool(mob.knockback_resistance)) {
        setKnockbackResistance(Mob, MobType, config);
    }
    if (bool(mob.luck)) {
        setLuck(Mob, MobType, config);
    }
    if (bool(mob.follow_range)) {
        setFllowRange(Mob, MobType, config);
    }
    if (bool(mob.speed.lava_speed)) {
        setSpeed(Mob, MobType, config, "lava_speed");
    }
    if (bool(mob.speed.water_speed)) {
        setSpeed(Mob, MobType, config, "water_speed");
    }
}
namespace Strengthen {

Strengthen::Strengthen() = default;

Strengthen& Strengthen::getInstance() {
    static Strengthen instance;
    return instance;
}

ll::plugin::NativePlugin& Strengthen::getSelf() const { return *mSelf; }

bool Strengthen::load(ll::plugin::NativePlugin& self) {
    mSelf        = std::addressof(self);
    auto& logger = getSelf().getLogger();

    const auto& configFilePath = self.getConfigDir() / "config.json";
    if (!ll::config::loadConfig(mConfig, configFilePath)) {
        logger.warn("Cannot load configurations from {}", configFilePath);
        logger.info("Saving default configurations");

        if (!ll::config::saveConfig(mConfig, configFilePath)) {
            logger.error("Cannot save default configurations to {}", configFilePath);
        }
    }


    getSelf().getLogger().info("loading...");

    // Code for loading the plugin goes here.

    return true;
}

bool Strengthen::enable() {
    getSelf().getLogger().info("enabling...");

    auto& logger = getSelf().getLogger();

    auto& EventBus = ll::event::EventBus::getInstance();

    mMobSpawned = EventBus.emplaceListener<ll::event::SpawnedMobEvent>([this](ll::event::SpawnedMobEvent& event) {
        if (!event.mob().has_value()) return true;
        auto Mob      = event.mob();
        auto TypeName = Mob->getTypeName();
        if (TypeName == "minecraft:blaze") {
            setAttribute(Mob, this->mConfig, MonsterList::blaze);
        } else if (TypeName == "minecraft:creeper") {
            setAttribute(Mob, this->mConfig, MonsterList::creeper);
        } else if (TypeName == "minecraft:drowned") {
            setAttribute(Mob, this->mConfig, MonsterList::drowned);
        } else if (TypeName == "minecraft:enderman") {
            setAttribute(Mob, this->mConfig, MonsterList::enderman);
        } else if (TypeName == "minecraft:evoker") {
            setAttribute(Mob, this->mConfig, MonsterList::evoker);
        } else if (TypeName == "minecraft:ghast") {
            setAttribute(Mob, this->mConfig, MonsterList::ghast);
        } else if (TypeName == "minecraft:guardian") {
            setAttribute(Mob, this->mConfig, MonsterList::guardian);
        } else if (TypeName == "minecraft:elder_guardian") {
            setAttribute(Mob, this->mConfig, MonsterList::elder_guardian);
        } else if (TypeName == "minecraft:husk") {
            setAttribute(Mob, this->mConfig, MonsterList::husk);
        } else if (TypeName == "minecraft:magma_cube") {
            setAttribute(Mob, this->mConfig, MonsterList::magma_cube);
        } else if (TypeName == "minecraft:endermite") {
            setAttribute(Mob, this->mConfig, MonsterList::endermite);
        } else if (TypeName == "minecraft:hoglin") {
            setAttribute(Mob, this->mConfig, MonsterList::hoglin);
        } else if (TypeName == "minecraft:phantom") {
            setAttribute(Mob, this->mConfig, MonsterList::phantom);
        } else if (TypeName == "minecraft:piglin_brute") {
            setAttribute(Mob, this->mConfig, MonsterList::piglin_brute);
        } else if (TypeName == "minecraft:pillager") {
            setAttribute(Mob, this->mConfig, MonsterList::pillager);
        } else if (TypeName == "minecraft:ravager") {
            setAttribute(Mob, this->mConfig, MonsterList::ravager);
        } else if (TypeName == "minecraft:shulker") {
            setAttribute(Mob, this->mConfig, MonsterList::shulker);
        } else if (TypeName == "minecraft:silverfish") {
            setAttribute(Mob, this->mConfig, MonsterList::silverfish);
        } else if (TypeName == "minecraft:skeleton") {
            setAttribute(Mob, this->mConfig, MonsterList::skeleton);
        } else if (TypeName == "minecraft:vex") {
            setAttribute(Mob, this->mConfig, MonsterList::vex);
        } else if (TypeName == "minecraft:vindicator") {
            setAttribute(Mob, this->mConfig, MonsterList::vindicator);
        } else if (TypeName == "minecraft:warden") {
            setAttribute(Mob, this->mConfig, MonsterList::warden);
        } else if (TypeName == "minecraft:witch") {
            setAttribute(Mob, this->mConfig, MonsterList::witch);
        } else if (TypeName == "minecraft:wither_skeleton") {
            setAttribute(Mob, this->mConfig, MonsterList::wither_skeleton);
        } else if (TypeName == "minecraft:zoglin") {
            setAttribute(Mob, this->mConfig, MonsterList::zoglin);
        } else if (TypeName == "minecraft:zombie") {
            setAttribute(Mob, this->mConfig, MonsterList::zombie);
        } else if (TypeName == "minecraft:zombie_villager_v2") {
            setAttribute(Mob, this->mConfig, MonsterList::zombie_villager_v2);
        } else if (TypeName == "minecraft:piglin") {
            setAttribute(Mob, this->mConfig, MonsterList::piglin);
        } else if (TypeName == "minecraft:slime") {
            setAttribute(Mob, this->mConfig, MonsterList::slime);
        } else if (TypeName == "minecraft:cave_spider") {
            setAttribute(Mob, this->mConfig, MonsterList::cave_spider);
        } else if (TypeName == "minecraft:spider") {
            setAttribute(Mob, this->mConfig, MonsterList::spider);
        } else if (TypeName == "minecraft:zombie_pigman") {
            setAttribute(Mob, this->mConfig, MonsterList::zombie_pigman);
        } else if (TypeName == "minecraft:stray") {
            setAttribute(Mob, this->mConfig, MonsterList::stray);
        } else if (TypeName == "minecraft:ender_dragon") {
            setAttribute(Mob, this->mConfig, MonsterList::ender_dragon);
        } else if (TypeName == "minecraft:wither") {
            setAttribute(Mob, this->mConfig, MonsterList::wither);
        }


        return true;
    });
    return true;
}


bool Strengthen::disable() {
    getSelf().getLogger().info("disabling...");
    auto& EventBus = ll::event::EventBus::getInstance();

    EventBus.removeListener(mMobSpawned);

    // Code for disabling the plugin goes here.

    return true;
}

extern "C" {
_declspec(dllexport) bool ll_plugin_load(ll::plugin::NativePlugin& self) {
    return Strengthen::getInstance().load(self);
}

_declspec(dllexport) bool ll_plugin_enable(ll::plugin::NativePlugin&) { return Strengthen::getInstance().enable(); }

_declspec(dllexport) bool ll_plugin_disable(ll::plugin::NativePlugin&) { return Strengthen::getInstance().disable(); }

/// @warning Unloading the plugin may cause a crash if the plugin has not released all of its
/// resources. If you are unsure, keep this function commented out.
// _declspec(dllexport) bool ll_plugin_unload(ll::plugin::NativePlugin&) {
//     return Strengthen::getInstance().unload();
// }
}

} // namespace Strengthen
