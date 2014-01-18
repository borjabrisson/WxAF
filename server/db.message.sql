create table if not exists message(
	messageID integer auto_increment,
	owner varchar(20), -- FK a la tabla de usuarios.
	subject varchar(150),
	content varchar(600),
	attached boolean, -- De momento será booleanos. Podria ser un ID varchar y en el caso que sea null representa el otro caso.
	PRIMARY KEY (messageID)
-- 	foreign key (owner) references users(userID) on delete RESTRICT on update cascade,
-- 	foreign key (item) references item(item) on delete RESTRICT on update RESTRICT
) engine InnoDB, default character set utf8;

create table if not exists notify_Message(
	notifyID integer auto_increment,
	messageID integer ,
	receiver varchar(20), -- FK a la tabla de usuarios.
	state enum('no-notify','notified','read','deleted','owner'), -- Como emular el owner??
	PRIMARY KEY (notifyID),
	foreign key (messageID) references message(messageID) on delete RESTRICT on update cascade
-- 	foreign key (item) references item(item) on delete RESTRICT on update RESTRICT
) engine InnoDB, default character set utf8;