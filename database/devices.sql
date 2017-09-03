BEGIN TRANSACTION;
CREATE TABLE "socket" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT,
	`type`	TEXT
);
INSERT INTO `socket` (id,name,type) VALUES (1,'X','in'),
 (2,'Y','out'),
 (3,'X1','in'),
 (4,'X2','in');
CREATE TABLE `device_socket` (
	`device_id`	INTEGER,
	`socket_id`	INTEGER,
	FOREIGN KEY(`device_id`) REFERENCES device,
	FOREIGN KEY(`socket_id`) REFERENCES socket
);
INSERT INTO `device_socket` (device_id,socket_id) VALUES (1,1),
 (1,2),
 (2,3),
 (2,4),
 (2,2),
 (3,3),
 (3,4),
 (3,2);
CREATE TABLE "device" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`category_id`	INTEGER,
	`short_name`	TEXT,
	`full_name`	TEXT,
	`truth_table_file`	TEXT,
	`image_file`	TEXT,
	FOREIGN KEY(`category_id`) REFERENCES category
);
INSERT INTO `device` (id,category_id,short_name,full_name,truth_table_file,image_file) VALUES (1,1,'NOT','Инвертор',NULL,NULL),
 (2,1,'AND','Элемент 2И',NULL,NULL),
 (3,1,'NAND','Элемент 2И-НЕ',NULL,NULL);
CREATE TABLE `category` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL
);
INSERT INTO `category` (id,name) VALUES (1,'Логические элементы'),
 (2,'Триггеры');
COMMIT;
