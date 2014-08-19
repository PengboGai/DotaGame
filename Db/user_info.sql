/*
Navicat MySQL Data Transfer

Source Server         : 192.168.25.212
Source Server Version : 50172
Source Host           : 192.168.25.212:3306
Source Database       : u3ddata2

Target Server Type    : MYSQL
Target Server Version : 50172
File Encoding         : 65001

Date: 2014-08-19 13:43:30
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `user_info`
-- ----------------------------
DROP TABLE IF EXISTS `user_info`;
CREATE TABLE `user_info` (
  `id` int(4) unsigned NOT NULL AUTO_INCREMENT,
  `iggid` bigint(8) unsigned NOT NULL COMMENT '玩家id',
  `nickname` char(32) NOT NULL DEFAULT '' COMMENT '玩家昵称',
  `nickname_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '改名时间',
  `new_guide` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '新手引导步骤',
  `level` int(4) unsigned NOT NULL DEFAULT '1' COMMENT '战队等级',
  `exp` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '战队经验',
  `look` smallint(2) unsigned NOT NULL DEFAULT '0' COMMENT '头像',
  `coins` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '金钱',
  `gem` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '宝石',
  `gm` tinyint(4) unsigned NOT NULL DEFAULT '0' COMMENT '是否GM号（1是，0否）',
  `froce` tinyint(4) unsigned NOT NULL DEFAULT '0' COMMENT '是否被封号（1是，0否）',
  `create_timer` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
  `login_timer` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '最后登入时间',
  `logout_timer` bigint(8) unsigned NOT NULL DEFAULT '0' COMMENT '最后登出时间',
  `onlinetimes` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '在线时长',
  `loginip` char(16) NOT NULL DEFAULT '' COMMENT '最后登入时ip',
  `power` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '当前体力值',
  `power_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '体力值恢复倒计时',
  `skill_point` smallint(2) unsigned NOT NULL DEFAULT '0' COMMENT '卡牌技能点数',
  `skill_point_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '技能点恢复时间',
  `expedition_coins` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '远征币',
  `consortia_coins` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '工会币',
  `consortia_id` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '工会id',
  PRIMARY KEY (`id`),
  UNIQUE KEY `iggid` (`iggid`),
  KEY `nickname` (`nickname`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='数据表：玩家数据表';

-- ----------------------------
-- Records of user_info
-- ----------------------------
