select "Mensajes BD" as step;

create table if not exists message( 
	messageID integer auto_increment,
	owner varchar(15), -- FK a la tabla de usuarios.
	subject varchar(150),
	content varchar(600),
	dateSend date,
	timeSend time,
	attached boolean, -- De momento será booleanos. Podria ser un ID varchar y en el caso que sea null representa el otro caso.
	deletedByUser boolean default false,
	messageResponse integer default null, -- Nos indica a que hilo de conversación pertenece. El que sea null será el inicio. Los demás tendrán el ID de este.(facilidad de busqueda)
	PRIMARY KEY (messageID),
	foreign key (messageResponse) references message(messageID) on delete RESTRICT on update cascade,
	foreign key (owner) references Users(userID) on delete RESTRICT on update cascade
) engine InnoDB, default character set utf8;

create table if not exists notify_Message(
	notifyID integer auto_increment,
	messageID integer ,
	receiver varchar(20), -- FK a la tabla de usuarios.
	state enum('no-notify','notified','read','deleted'),
	PRIMARY KEY (notifyID),
	foreign key (messageID) references message(messageID) on delete RESTRICT on update cascade
) engine InnoDB, default character set utf8;
