

struct Speed {
    float speed       = 0;
    float lava_speed  = 0;
    float water_speed = 0;
};


struct Monster {
    float health               = 0;
    float attack               = 0;
    Speed speed                = {0, 0, 0};
    float luck                 = 0;
    float follow_range         = 0;
    float jump_strength        = 0;
    float knockback_resistance = 0;
};


struct Config {
    int version = 1;
    /** 烈焰人 */
    Monster blaze;
    /** 苦力怕 */
    Monster creeper;
    /** 溺尸 */
    Monster drowned;
    /** 末影人 */
    Monster enderman;
    /** 唤魔者 */
    Monster evoker;
    /** 恶魂 */
    Monster ghast;
    /** 守卫者 */
    Monster guardian;
    /** 远古守卫者 */
    Monster elder_guardian;
    /** 尸壳 */
    Monster husk;
    /** 岩浆怪 */
    Monster magma_cube;
    /** 末影螨 */
    Monster endermite;
    /** 疣猪兽 */
    Monster hoglin;
    /** 幻翼 */
    Monster phantom;
    /** 猪灵蛮兵 */
    Monster piglin_brute;
    /** 掠夺者 */
    Monster pillager;
    /** 劫掠兽 */
    Monster ravager;
    /** 潜影贝 */
    Monster shulker;
    /** 蠹虫 */
    Monster silverfish;
    /** 骷髅 */
    Monster skeleton;
    /** 恼鬼 */
    Monster vex;
    /** 卫道士 */
    Monster vindicator;
    /** 监守者 */
    Monster warden;
    /** 女巫 */
    Monster witch;
    /** 凋零骷髅 */
    Monster wither_skeleton;
    /** 僵尸疣猪兽 */
    Monster zoglin;
    /** 僵尸 */
    Monster zombie;
    /** 僵尸村民 */
    Monster zombie_villager_v2;
    /** 猪灵 */
    Monster piglin;
    /** 史莱姆 */
    Monster slime;
    /** 洞穴蜘蛛 */
    Monster cave_spider;
    /** 蜘蛛 */
    Monster spider;
    /** 僵尸猪灵 */
    Monster zombie_pigman;
    /** 流浪者 */
    Monster stray;
    /** 末影龙 */
    Monster ender_dragon;
    /** 凋零 */
    Monster wither;
};