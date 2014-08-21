
DROP DATABASE IF EXISTS dota_game;
CREATE DATABASE dota_game;
USE dota_game;

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` bigint(8) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `nick_name` varchar(20) NOT NULL DEFAULT '' COMMENT '玩家昵称',
  `team_level` int(4) unsigned NOT NULL DEFAULT '1' COMMENT '战队等级',
  `change_name_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '改名时间',
  `team_exp` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '战队经验',
  `head_id` smallint(2) unsigned NOT NULL DEFAULT '0' COMMENT '头像',
  `gold` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '金币',
  `diamond` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '宝石',
  `power` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '当前体力值',
  `power_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '体力值恢复倒计时',
  `skill_point` smallint(2) unsigned NOT NULL DEFAULT '0' COMMENT '卡牌技能点数',
  `expedition_money` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '远征币',
  `skill_point_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '技能点恢复时间',
  `new_guide` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '新手引导步骤',
  `freeze` tinyint(4) unsigned NOT NULL DEFAULT '0' COMMENT '是否被封号（1是，0否）',
  `create_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
  `login_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '最后登入时间',
  `logout_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '最后登出时间',
  `login_ip` char(16) NOT NULL DEFAULT '' COMMENT '最后登入时ip',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`user_id`),
  UNIQUE KEY (`nick_name`)
) ENGINE=InnoDB AUTO_INCREMENT=10000 DEFAULT CHARSET=utf8;