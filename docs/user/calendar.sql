select "Calendario BD" as step;

create table if not exists notebook(
	noteID integer unsigned auto_increment,
	dateNote date not null,
	timeNote time not null,
	description varchar(50),
	daysToNotify integer default 1,
	judgmentCode varchar(16),
	PRIMARY KEY (noteID),
	foreign key (judgmentCode) references Judgments(judgmentCode) on delete cascade on update cascade
) engine InnoDB, default character set utf8;

create table if not exists comment_Note(
	commentID integer unsigned auto_increment,
	noteID integer unsigned,
	commentNote varchar(120),
	PRIMARY KEY (commentID),
	foreign key (noteID) references notebook(noteID) on delete cascade on update cascade
) engine InnoDB, default character set utf8;
