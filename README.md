# <center> 自定义生成的怪物

## 插件介绍及功能

**根据你的需要,修改原版生物的各种属性**

目前已支持的属性有

- absorption：吸收
- attack：攻击伤害
- follow_range：跟随范围
- health：生命值
- jump_strength：跳跃强度
- knockback_resistance：击退抵抗
- lava_movement_speed：熔岩移动速度
- luck：幸运
- movement_speed：移动速度
- underwater_movement_speed：水下移动速度

注意:请适量修改,否则你可能见不到怪物 (因为跑太快了哈哈哈)

## 插件加载

1.  手动安装

    将下载的压缩包解压到`path/to/bds/plugins` 文件夹下

        包括文件夹夹一起 否则会加载不上

2.  使用`lip`包管理器安装

        使用命令: `lip install github.com/xianyubb/Strengthen`

## 配置文件

<center> <b>配置文件几乎为一种格式</b> </center>

例如烈焰人:

```json
  "blaze": {
    "health": 0.0,
    "attack": 0.0,
    "speed": {
      "speed": 0.0,
      "lava_speed": 0.0,
      "water_speed": 0.0
    },
    "luck": 0.0,
    "follow_range": 0.0,
    "jump_strength": 0.0,
    "knockback_resistance": 0.0
  }
```
其他怪物的也如此

**默认配置文件为0.0 即不改变原来的属性值**

需要更改的话只需要更改后面的数字即可

## 插件支持版本

BedRock Dedicated Server 1.20.51 协议 630

LeviLamina 0.7.2

## 插件作者及联系方式

Author: xianyubb

QQ: 2149656630

QQGroup: 865286891

## License

CC0-1.0 © LiteLDev
