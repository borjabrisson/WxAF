-- /*SuperType*/
select "Contacts BD" as step;
Create Table SuperType (
	ID integer unsigned auto_increment primary key
) engine InnoDB, default character set utf8;

Create Table Company(
	ID integer unsigned auto_increment,
	name varchar(50),
	address varchar (35),
	email varchar(20),
	CIF varchar(10),
	web varchar(12),
	contact varchar(15),
	Constraint PK_Company Primary key (ID),
	foreign key (ID) references SuperType(ID) On Delete Cascade On Update Cascade
) engine InnoDB, default character set utf8;

-- /*Abogado*/
Create Table Lawyers(
	ID integer unsigned,
	lawyerNumber  integer unsigned,
	name varchar(30),
	surnames varchar(40),
	address varchar (35),
	email varchar(30),
	Constraint Unique_Lawyer_Number unique(lawyerNumber),
	-- Atención!!: Hay que revisar que el null no de problemas con el unique: DONE: El null como tal no influye, pero si el "".
	Constraint PK_lawyer Primary key (ID),
	foreign key (ID) references SuperType(ID) On Delete Cascade On Update Cascade
) engine InnoDB, default character set utf8;

-- /*Procurador*/
Create Table Attorneys(
	ID integer unsigned,
	attorneyNumber integer unsigned,
	name varchar(30),
	surnames varchar(40),
	address varchar (35),
	email varchar(30),
	Constraint Unique_Attorney_Number unique (attorneyNumber),
	Constraint PK_attorney Primary key (ID),
	foreign key (ID) references SuperType(ID) On Delete Cascade On Update Cascade
) engine InnoDB, default character set utf8;

-- /*CLiente*/
Create Table Clients (
	ID integer unsigned,
	DNI char(9) ,
	name varchar(30),
	surnames varchar(40),
	address varchar (35),
	email varchar(30),
	Constraint Unique_DNI unique(DNI),
	Constraint PK_Clients Primary key (ID),
	foreign key (ID) references SuperType(ID) On Delete Cascade On Update Cascade
) engine InnoDB, default character set utf8;

-- -- Tablas relacionales (Relaciones multiples)