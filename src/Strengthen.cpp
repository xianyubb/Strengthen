#include "Strengthen.h"

#include "ll/api/Config.h"
#include "ll/api/Logger.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/world/SpawnMobEvent.h"
#include "ll/api/utils/HashUtils.h"
#include "mc/common/wrapper/optional_ref.h"
#include "mc/world/actor/Mob.h"
#include "mc/world/attribute/AttributeInstance.h"
#include "mc/world/attribute/SharedAttributes.h"

#include <ll/api/plugin/NativePlugin.h>
#include <memory>
#include <stdexcept>

ll::Logger logger;

void setAttribute(optional_ref<Mob>& Mob, MonsterList MobType) {
    // logger.info(Mob->getTypeName());
    auto mob = getMob(MobType, mConfig);
    try {

        if (bool(mob.attack)) {
            Mob->getMutableAttribute(SharedAttributes::ATTACK_DAMAGE)->setMaxValue(mob.attack);
            Mob->getMutableAttribute(SharedAttributes::ATTACK_DAMAGE)->setCurrentValue(mob.attack);
        }
        if (bool(mob.health)) {
            Mob->getMutableAttribute(SharedAttributes::HEALTH)->setMaxValue(mob.health);
            Mob->getMutableAttribute(SharedAttributes::HEALTH)->setCurrentValue(mob.health);
        }
        if (bool(mob.speed.speed)) {
            Mob->getMutableAttribute(SharedAttributes::MOVEMENT_SPEED)->setMaxValue(mob.speed.speed);
            Mob->getMutableAttribute(SharedAttributes::MOVEMENT_SPEED)->setCurrentValue(mob.speed.speed);
        }
        if (bool(mob.speed.lava_speed)) {
            Mob->getMutableAttribute(SharedAttributes::LAVA_MOVEMENT_SPEED)->setMaxValue(mob.speed.lava_speed);
            Mob->getMutableAttribute(SharedAttributes::LAVA_MOVEMENT_SPEED)->setCurrentValue(mob.speed.lava_speed);
        }
        if (bool(mob.speed.water_speed)) {
            Mob->getMutableAttribute(SharedAttributes::UNDERWATER_MOVEMENT_SPEED)->setMaxValue(mob.speed.water_speed);
            Mob->getMutableAttribute(SharedAttributes::UNDERWATER_MOVEMENT_SPEED)
                ->setCurrentValue(mob.speed.water_speed);
        }
        if (bool(mob.jump_strength)) {
            Mob->getMutableAttribute(SharedAttributes::JUMP_STRENGTH)->setMaxValue(mob.jump_strength);
            Mob->getMutableAttribute(SharedAttributes::JUMP_STRENGTH)->setCurrentValue(mob.jump_strength);
        }
        if (bool(mob.knockback_resistance)) {
            Mob->getMutableAttribute(SharedAttributes::KNOCKBACK_RESISTANCE)->setMaxValue(mob.knockback_resistance);
            Mob->getMutableAttribute(SharedAttributes::KNOCKBACK_RESISTANCE)->setCurrentValue(mob.knockback_resistance);
        }
        if (bool(mob.follow_range)) {
            Mob->getMutableAttribute(SharedAttributes::FOLLOW_RANGE)->setMaxValue(mob.follow_range);
            Mob->getMutableAttribute(SharedAttributes::FOLLOW_RANGE)->setCurrentValue(mob.follow_range);
        }
    } catch (std::runtime_error& err) {

        // logger.info(err.what());
    }
}

// LL_TYPE_INSTANCE_HOOK(
//     SpawnedMobEventHook,
//     HookPriority::Normal,
//     Spawner,
//     &Spawner::spawnMob,
//     Mob*,
//     BlockSource&                     blockSource,
//     ActorDefinitionIdentifier const& id,
//     Actor*                           spawner,
//     Vec3 const&                      pos,
//     bool                             naturalSpawn,
//     bool                             surface,
//     bool                             fromSpawner
// ) {
//     auto res = origin(blockSource, id, spawner, pos, naturalSpawn, surface, fromSpawner);
//
//
//     return res;
// }


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
    auto& evnetBus = ll::event::EventBus::getInstance();

    evnetBus.emplaceListener<ll::event::SpawnedMobEvent>([](ll::event::SpawnedMobEvent& ev) {
        // if (ev.mob() == nullptr) return true;
        if (!ev.mob().has_value()) return true;
        auto res = ev.mob();
            switch (ll::hash_utils::doHash(res->getTypeName())) {
            case ll::hash_utils::doHash("minecraft:blaze"): {
                setAttribute(res, MonsterList::blaze);
                break;
            }
            case ll::hash_utils::doHash("minecraft:creeper"): {
                setAttribute(res, MonsterList::creeper);
                break;
            }
            case ll::hash_utils::doHash("minecraft:drowned"): {
                setAttribute(res, MonsterList::drowned);
                break;
            }
            case ll::hash_utils::doHash("minecraft:enderman"): {
                setAttribute(res, MonsterList::enderman);
                break;
            }
            case ll::hash_utils::doHash("minecraft:evoker"): {
                setAttribute(res, MonsterList::evoker);
                break;
            }
            case ll::hash_utils::doHash("minecraft:ghast"): {
                setAttribute(res, MonsterList::ghast);
                break;
            }
            case ll::hash_utils::doHash("minecraft:guardian"): {
                setAttribute(res, MonsterList::guardian);
                break;
            }
            case ll::hash_utils::doHash("minecraft:elder_guardian"): {
                setAttribute(res, MonsterList::elder_guardian);
                break;
            }
            case ll::hash_utils::doHash("minecraft:husk"): {
                setAttribute(res, MonsterList::husk);
                break;
            }
            case ll::hash_utils::doHash("minecraft:magma_cube"): {
                setAttribute(res, MonsterList::magma_cube);
                break;
            }
            case ll::hash_utils::doHash("minecraft:endermite"): {
                setAttribute(res, MonsterList::endermite);
                break;
            }
            case ll::hash_utils::doHash("minecraft:hoglin"): {
                setAttribute(res, MonsterList::hoglin);
                break;
            }
            case ll::hash_utils::doHash("minecraft:phantom"): {
                setAttribute(res, MonsterList::phantom);
                break;
            }
            case ll::hash_utils::doHash("minecraft:piglin_brute"): {
                setAttribute(res, MonsterList::piglin_brute);
                break;
            }
            case ll::hash_utils::doHash("minecraft:pillager"): {
                setAttribute(res, MonsterList::pillager);
                break;
            }
            case ll::hash_utils::doHash("minecraft:ravager"): {
                setAttribute(res, MonsterList::ravager);
                break;
            }
            case ll::hash_utils::doHash("minecraft:shulker"): {
                setAttribute(res, MonsterList::shulker);
                break;
            }
            case ll::hash_utils::doHash("minecraft:silverfish"): {
                setAttribute(res, MonsterList::silverfish);
                break;
            }
            case ll::hash_utils::doHash("minecraft:skeleton"): {
                setAttribute(res, MonsterList::skeleton);
                break;
            }
            case ll::hash_utils::doHash("minecraft:vex"): {
                setAttribute(res, MonsterList::vex);
                break;
            }
            case ll::hash_utils::doHash("minecraft:vindicator"): {
                setAttribute(res, MonsterList::vindicator);
                break;
            }
            case ll::hash_utils::doHash("minecraft:warden"): {
                setAttribute(res, MonsterList::warden);
                break;
            }
            case ll::hash_utils::doHash("minecraft:witch"): {
                setAttribute(res, MonsterList::witch);
                break;
            }
            case ll::hash_utils::doHash("minecraft:wither_skeleton"): {
                setAttribute(res, MonsterList::wither_skeleton);
                break;
            }
            case ll::hash_utils::doHash("minecraft:zoglin"): {
                setAttribute(res, MonsterList::zoglin);
                break;
            }
            case ll::hash_utils::doHash("minecraft:zombie"): {
                setAttribute(res, MonsterList::zombie);
                break;
            }
            case ll::hash_utils::doHash("minecraft:zombie_villager_v2"): {
                setAttribute(res, MonsterList::zombie_villager_v2);
                break;
            }
            case ll::hash_utils::doHash("minecraft:piglin"): {
                setAttribute(res, MonsterList::piglin);
                break;
            }
            case ll::hash_utils::doHash("minecraft:slime"): {
                setAttribute(res, MonsterList::slime);
                break;
            }
            case ll::hash_utils::doHash("minecraft:cave_spider"): {
                setAttribute(res, MonsterList::cave_spider);
                break;
            }
            case ll::hash_utils::doHash("minecraft:spider"): {
                setAttribute(res, MonsterList::spider);
                break;
            }
            case ll::hash_utils::doHash("minecraft:zombie_pigman"): {
                setAttribute(res, MonsterList::zombie_pigman);
                break;
            }
            case ll::hash_utils::doHash("minecraft:stray"): {
                setAttribute(res, MonsterList::stray);
                break;
            }
            case ll::hash_utils::doHash("minecraft:ender_dragon"): {
                setAttribute(res, MonsterList::ender_dragon);
                break;
            }
            case ll::hash_utils::doHash("minecraft:wither"): {
                setAttribute(res, MonsterList::wither);
                break;
            }
            }
        return true;
    });
    // auto& logger = getSelf().getLogger();

    return true;
}


bool Strengthen::disable() {
    getSelf().getLogger().info("disabling...");

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
