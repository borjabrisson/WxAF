select "Judgments BD" as step;

-- Esta tabla permitirá configurar la representacion de los expedientes de cada usuario.
Create Table Configuration (
	ID integer primary key,
	fileNumber integer unsigned,
	prefix varchar(6)default "", -- Contenido previo a la fecha (con formato)
	lastDate varchar(10)default "", -- Indica la ultima fecha usada, indicando a partir de cual se resetea.
	formatDate varchar(6) default "%Y", -- Formato utilizado para mostrar la fecha.
	periodReset varchar (6)default "%Y", -- Indica el formato a utilizar para crear la fecha de reseteo. Si es por año, por trimestre, combinaciones, etc.
	divisor varchar(4) default "/" -- Separa la fecha formateada del numero de expediente.
) engine InnoDB, default character set utf8;

Insert Into Configuration (ID,fileNumber) values (1,0);

Create Table Files (
	fileCode varchar(16) primary key,
	openDate date not null,
	closeDate date,
	clientCode integer unsigned,
	observation varchar(120),
	Foreign key (clientCode) references Clients(ID) On Delete RESTRICT On Update Cascade
) engine InnoDB, default character set utf8;

-- /*Procedimiento*/
Create Table Judgments (-- judgments lawsuits
	judgmentCode varchar(16),
	fileCode varchar(16) not null,
	appealCode varchar(16), -- Codigo del recurso/apelacion
	startDate date not null,
	closeDate date,
	judgmentType varchar(10) not null, -- tipo de procedimiento
	courts integer unsigned not null,  -- Juzgado.
	nextEventDate date,
	nextEventHour time, -- En el mismo registro???
	observations varchar(500),
	Constraint Judgments Primary Key (judgmentCode),
	Foreign key (appealCode) references Judgments (judgmentCode) On Delete RESTRICT On Update Cascade,
	Foreign key (courts) references agosal2.Courts (CourtCode) On Delete RESTRICT On Update Cascade, -- Registros comentados a la espera de hacer la division de BD.
	Foreign key (judgmentType) references agosal2.judgmentType (Type) On Delete RESTRICT On Update Cascade,
	Foreign key (fileCode) references Files (fileCode) On Delete Cascade On Update Cascade,
	Constraint appealCode Unique (appealCode)
) engine InnoDB, default character set utf8;

-- Esta tabla podria hacerse global como el caso de los tipos de Procedimiento
Create Table type_writs (
	type varchar(10) primary key,
	description varchar(20)
) engine InnoDB, default character set utf8;

Create Table associatedDocuments  (
	documentCode integer unsigned,
	judgmentCode varchar(16) not null,
	type varchar(10) not null,
-- 	Documento BLOB,
	Document varchar(40),
	name varchar(20) not null,
	expirationDate Date,
	creationDate Date not null,
	modifyDate timestamp not null,
	Constraint PK_associatedDocuments Primary Key (documentCode),
	Foreign key (judgmentCode) references Judgments (judgmentCode) On Delete Cascade On Update Cascade,
	Foreign key (type) references type_writs (type) On Delete RESTRICT On Update Cascade
) engine InnoDB, default character set utf8;

-- /*Propiedades Multievaluada Contrarios*/
Create Table Opposite (
	judgmentCode varchar(16) not null,
	oppositeClient_Code  integer unsigned not null,
	oppositeCounsel_Code integer unsigned ,
	oppositeAttorney_Code integer unsigned ,
	Constraint PK_Opposite Primary Key (judgmentCode, oppositeClient_Code, oppositeCounsel_Code,oppositeAttorney_Code),
	Foreign key (judgmentCode) references Judgments (judgmentCode) On Delete Cascade On Update Cascade,
	Foreign key (oppositeCounsel_Code) references Lawyers(ID) On Delete RESTRICT On Update Cascade,
	Foreign key (oppositeAttorney_Code) references Attorneys (ID) On Delete RESTRICT On Update Cascade,
	Foreign key (oppositeClient_Code) references Clients(ID) On Delete RESTRICT On Update Cascade,
	Constraint OppsiteClient_Unique Unique (judgmentCode,oppositeClient_Code)
) engine InnoDB, default character set utf8;

-- /*Propiedades Multievaluada Defendidos*/
Create Table Defense (
	judgmentCode varchar(16) not null,
	defenseClient_Code integer unsigned not null,
	defenseCounsel_Code integer unsigned , -- lawyer
	defenseAttorney_Code integer unsigned ,
	Constraint PF_Defense Primary Key (judgmentCode, defenseClient_Code, defenseCounsel_Code,defenseAttorney_Code),
	Foreign key (judgmentCode) references Judgments (judgmentCode) On Delete Cascade On Update Cascade,
	Foreign key (defenseCounsel_Code) references Lawyers (ID) On Delete RESTRICT On Update Cascade,
	Foreign key (defenseAttorney_Code) references Attorneys (ID) On Delete RESTRICT On Update Cascade,
	Foreign key (defenseClient_Code) references Clients(ID) On Delete RESTRICT On Update Cascade,
	Constraint DefenseClient_Unique Unique (judgmentCode,defenseClient_Code)
) engine InnoDB, default character set utf8;


--  RSA: Que los abogados, clientes o procuradores no esten en defensa o contrarios para el mismo caso.

-- CREATE ASSERTION Restriccion_Abogados CHECK (NOT EXISTS (SELECT * FROM Defendidos D, Contrarios C
-- 	WHERE D.judgmentCode = C.judgmentCode and CodAbog_Cont = CodAbog_Defendido));
-- 	
-- CREATE ASSERTION Restriccion_Procuradores CHECK (NOT EXISTS (SELECT * FROM Defendidos D, Contrarios C
-- 	WHERE D.judgmentCode = C.judgmentCode and CodProc_Defendido = CodProc_Cont));
-- 
-- CREATE ASSERTION Restriccion_Clientes CHECK (NOT EXISTS (SELECT * FROM Defendidos D, Contrarios C
-- 	WHERE D.judgmentCode = C.judgmentCode and C.Contrario = D.Defendido));
