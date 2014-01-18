-- BD genérica.

--  Tipo de Juzgados
Create Table courtsType (
	Type varchar(10) primary key,
	descripcion varchar(20)
) engine InnoDB, default character set utf8;

--  Tipo de procedimientos
Create Table judgmentType (
	Type varchar(10) primary key,
	descripcion varchar(20)
) engine InnoDB, default character set utf8;

Create Table Community (
	ID varchar(5) primary key,
	descripcion varchar(20)
) engine InnoDB, default character set utf8;

Create Table Users (
	userID varchar(15) not null,
	SystemID integer unsigned auto_increment primary key,
	Name varchar(20),
	Surnames varchar(25),
	Gender enum("H","M"),
	Email varchar(20),
	Community varchar(5),
	Constraint Unique_userID unique (userID), -- Inicialmente era el PK, pero la imposibilidad de utilizar el auto increment en un campo no PK nos obliga a esto.
	foreign key (community) references Community(ID) On Delete RESTRICT On Update Cascade
) engine InnoDB, default character set utf8;

-- /* Juzeces*/
Create Table Judges (
	JudgeCode integer unsigned auto_increment,
	Name varchar(28),
	Surnames varchar(20),
	Constraint Judges Primary Key (JudgeCode)
) engine InnoDB, default character set utf8;

-- /*Secretarios*/
Create Table Secretaries (
	SecretaryCode integer unsigned auto_increment,
	Name varchar(28),
	Surnames varchar(20),
	Constraint Secretaries Primary Key (SecretaryCode)
) engine InnoDB, default character set utf8;


-- /*Supertipo: Juzgados*/
Create Table Courts (
	CourtCode integer unsigned auto_increment,
	JudgeCode integer unsigned, -- *
	SecretaryCode integer unsigned, -- * No deberian permitir el nulo, pero la practica y la administracion nos recomienda esto.Y si de momento no sabes quien es??
	Address varchar (40),
	Type varchar(10) not null,
	Community varchar(5) not null,
	Constraint Courts Primary Key (CourtCode),
	foreign key (JudgeCode) references Judges(JudgeCode) On Delete RESTRICT On Update Cascade,
	foreign key (SecretaryCode) references Secretaries (SecretaryCode) On Delete RESTRICT On Update Cascade,
	foreign key (Type) references courtsType (Type) On Delete RESTRICT On Update Cascade,
	-- /* RSA 3*/
	Constraint RSA3_1_JudgesUnique Unique (JudgeCode),
	Constraint RSA3_2_SecretaryUnique Unique (SecretaryCode)
) engine InnoDB, default character set utf8;


-- foreign key (question) references questions(id) on delete RESTRICT on update cascade