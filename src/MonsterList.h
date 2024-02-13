
#include "Config.h"


enum class MonsterList {
    blaze,
    creeper,
    drowned,
    enderman,
    evoker,
    ghast,
    guardian,
    elder_guardian,
    husk,
    magma_cube,
    endermite,
    hoglin,
    phantom,
    piglin_brute,
    pillager,
    ravager,
    shulker,
    silverfish,
    skeleton,
    vex,
    vindicator,
    warden,
    witch,
    wither_skeleton,
    zoglin,
    zombie,
    zombie_villager_v2,
    piglin,
    slime,
    cave_spider,
    spider,
    zombie_pigman,
    stray,
    ender_dragon,
    wither
};


// 将 MonsterList 转换为字符串
Monster getMob(MonsterList monster, const Config& config) {
    switch (monster) {
    case MonsterList::blaze:
        return config.blaze;
    case MonsterList::creeper:
        return config.creeper;
    case MonsterList::drowned:
        return config.drowned;
    case MonsterList::enderman:
        return config.enderman;
    case MonsterList::evoker:
        return config.evoker;
    case MonsterList::ghast:
        return config.ghast;
    case MonsterList::guardian:
        return config.guardian;
    case MonsterList::elder_guardian:
        return config.elder_guardian;
    case MonsterList::husk:
        return config.husk;
    case MonsterList::magma_cube:
        return config.magma_cube;
    case MonsterList::endermite:
        return config.endermite;
    case MonsterList::hoglin:
        return config.hoglin;
    case MonsterList::phantom:
        return config.phantom;
    case MonsterList::piglin_brute:
        return config.piglin_brute;
    case MonsterList::pillager:
        return config.pillager;
    case MonsterList::ravager:
        return config.ravager;
    case MonsterList::shulker:
        return config.shulker;
    case MonsterList::silverfish:
        return config.silverfish;
    case MonsterList::skeleton:
        return config.skeleton;
    case MonsterList::vex:
        return config.vex;
    case MonsterList::vindicator:
        return config.vindicator;
    case MonsterList::warden:
        return config.warden;
    case MonsterList::witch:
        return config.witch;
    case MonsterList::wither_skeleton:
        return config.wither_skeleton;
    case MonsterList::zoglin:
        return config.zoglin;
    case MonsterList::zombie:
        return config.zombie;
    case MonsterList::zombie_villager_v2:
        return config.zombie_villager_v2;
    case MonsterList::piglin:
        return config.piglin;
    case MonsterList::slime:
        return config.slime;
    case MonsterList::cave_spider:
        return config.cave_spider;
    case MonsterList::spider:
        return config.spider;
    case MonsterList::zombie_pigman:
        return config.zombie_pigman;
    case MonsterList::stray:
        return config.stray;
    case MonsterList::ender_dragon:
        return config.ender_dragon;
    case MonsterList::wither:
        return config.wither;
    }
}