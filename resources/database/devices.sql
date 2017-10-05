BEGIN TRANSACTION;
CREATE TABLE "truth_table" (
	`device_id`	INTEGER,
	`socket_id`	INTEGER,
	`conditions`	TEXT,
	FOREIGN KEY(`device_id`) REFERENCES device,
	FOREIGN KEY(`socket_id`) REFERENCES socket
);
INSERT INTO `truth_table` (device_id,socket_id,conditions) VALUES (1,1,'0 1'),
 (1,2,'1 0'),
 (2,3,'0 0 1 1'),
 (2,4,'0 1 0 1'),
 (2,2,'0 0 0 1'),
 (3,3,'0 0 1 1'),
 (3,4,'0 1 0 1'),
 (3,2,'1 1 1 0'),
 (4,3,'0 0 1 1'),
 (4,4,'0 1 0 1'),
 (4,2,'0 1 1 1'),
 (5,3,'0 0 1 1'),
 (5,4,'0 1 0 1'),
 (5,2,'1 0 0 0');
CREATE TABLE "socket" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT,
	`type`	TEXT
);
INSERT INTO `socket` (id,name,type) VALUES (1,'X','in'),
 (2,'Y','out'),
 (3,'X1','in'),
 (4,'X2','in');
CREATE TABLE "device" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`category_id`	INTEGER,
	`short_name`	TEXT,
	`full_name`	TEXT,
	`image_file`	TEXT,
	FOREIGN KEY(`category_id`) REFERENCES category
);
INSERT INTO `device` (id,category_id,short_name,full_name,image_file) VALUES (1,1,'NOT','Инвертор','NOT.gif'),
 (2,1,'AND2','Элемент 2И','AND2.gif'),
 (3,1,'NAND2','Элемент 2И-НЕ','NAND2.gif'),
 (4,1,'OR2','Элемент 2ИЛИ','OR2.gif'),
 (5,1,'NOR2','Элемент 2ИЛИ-НЕ','NOR2.gif');
CREATE TABLE `category` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL
);
INSERT INTO `category` (id,name) VALUES (1,'Логические элементы'),
 (2,'Триггеры');
COMMIT;
