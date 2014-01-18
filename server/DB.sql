create table if not exists users(
	userID varchar(20) not null primary key,
	firstname  varchar(15),
	lastname  varchar(30),
	nickname varchar(10)
) engine InnoDB, default character set utf8;


select "Mensajes BD" as step;


create table if not exists message(
	messageID integer auto_increment,
	owner varchar(20), -- FK a la tabla de usuarios.
	subject varchar(150),
	content varchar(600),
	dateSend date,
	timeSend time,
	attached boolean, -- De momento será booleanos. Podria ser un ID varchar y en el caso que sea null representa el otro caso.
	deletedByUser boolean default false,
	messageResponse integer default null, -- Nos indica a que hilo de conversación pertenece. El que sea null será el inicio. Los demás tendrán el ID de este.(facilidad de busqueda)
	PRIMARY KEY (messageID),
	foreign key (messageResponse) references message(messageID) on delete RESTRICT on update cascade
-- 	foreign key (owner) references users(userID) on delete RESTRICT on update cascade,
) engine InnoDB, default character set utf8;

create table if not exists notify_Message(
	notifyID integer auto_increment,
	messageID integer ,
	receiver varchar(20), -- FK a la tabla de usuarios.
	state enum('no-notify','notified','read'), -- Como emular el owner??
	PRIMARY KEY (notifyID),
	foreign key (messageID) references message(messageID) on delete RESTRICT on update cascade
-- 	foreign key (item) references item(item) on delete RESTRICT on update RESTRICT
) engine InnoDB, default character set utf8;

select "Calendario BD" as step;

create table if not exists notebook(
	noteID integer auto_increment,
	dateNote date not null,
	timeNote time not null,
	description varchar(50),
	daysToNotify integer default 1,
	judProced varchar(20),
	owner varchar(20), -- FK a la tabla de usuarios.
	PRIMARY KEY (noteID)
-- 	foreign key (owner) references users(userID) on delete RESTRICT on update cascade
) engine InnoDB, default character set utf8;

create table if not exists comment_Note(
	commentID integer auto_increment,
	noteID integer ,
	commentNote varchar(120),
	PRIMARY KEY (commentID),
	foreign key (noteID) references notebook(noteID) on delete cascade on update cascade
) engine InnoDB, default character set utf8;

select "Contactos BD" as step;

create table if not exists contacts(
	contactID integer auto_increment,
	firstname varchar(20),
	lastname varchar(20),
	phone varchar(12),
	mobile varchar(12),
	address varchar(80),
	email varchar(50),
	owner varchar(20), -- FK a la tabla de usuarios del systema.
	userSystem varchar(20),
	PRIMARY KEY (contactID)
-- 	foreign key (noteID) references notebook(noteID) on delete cascade on update cascade
) engine InnoDB, default character set utf8;



