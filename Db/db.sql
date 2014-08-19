
-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `id` bigint(8) unsigned NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL DEFAULT '' COMMENT '用户名',
  `user_pwd` varchar(20) NOT NULL DEFAULT '' COMMENT '用户密码',
  `freeze` tinyint(4) unsigned NOT NULL DEFAULT '0' COMMENT '是否被封号（1是，0否）',
  `create_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
  `login_time` int(4) unsigned NOT NULL DEFAULT '0' COMMENT '最后登入时间',
  `login_ip` char(16) NOT NULL DEFAULT '0.0.0.0' COMMENT '最后登入时ip',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10000 DEFAULT CHARSET=utf8;