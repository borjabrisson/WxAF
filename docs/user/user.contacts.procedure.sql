select "Store Procedure User DB" as step;
delimiter $$

select "Contacts SP" as step$$

-- # Revisamos que los identificadores (CIF,DNI,Nº Profes) se repitan? o los "capturamos" por la restriccion unique
-- # Los deletes pueden ser agruparse en uno solo (por funcionalidad), pero por significado y futuros cambios mejor diferenciarlos.
-- ##! Queda por implementar la posibilidad de añadir profesionales desde el sistema.

-- #######################################################################################
-- ##########################	        	Empresas			##########################
-- #######################################################################################

drop procedure if exists new_Company$$
create procedure new_Company(
	in iname varchar(50),
	in iaddress varchar (35),
	in iemail varchar(20),
	in iCIF varchar(10),
	in iweb varchar(12),
	in icontact varchar(15)
)
begin
	declare iID integer;
	insert into SuperType() values ();
	SELECT LAST_INSERT_ID() into iID;
	
	insert into Company(ID,name,address,email,CIF,web,contact)
				 values(iID,iname,iaddress,iemail,iCIF,iweb,icontact);
	select 0 as error;
end$$

drop procedure if exists edit_Company$$
create procedure edit_Company(
	in iID integer,
	in iname varchar(50),
	in iaddress varchar (35),
	in iemail varchar(20),
	in iCIF varchar(10),
	in iweb varchar(12),
	in icontact varchar(15)
)
begin
	update Company set name=iname,address=iaddress,email=iemail,
					CIF=iCIF,web=iweb,contact=icontact where ID=iID;
	select 0 as error;
end$$

drop procedure if exists delete_Company$$
create procedure delete_Company(
	in iID integer
)
begin
	delete from SuperType where ID = iID;
	select 0 as error;
end$$

-- #######################################################################################
-- ##########################	        	Abogados			##########################
-- #######################################################################################

drop procedure if exists new_Lawyers$$
create procedure new_Lawyers(
	in ilawyerNumber  integer unsigned,
	in iname varchar(30),
	in isurnames varchar(40),
	in iaddress varchar (35),
	in iemail varchar(20)
)
begin
	declare iID integer;
	insert into SuperType() values ();
	SELECT LAST_INSERT_ID() into iID;
	
	insert into Lawyers(ID,lawyerNumber,name,surnames,address,email)
				 values(iID,ilawyerNumber,iname,isurnames,iaddress,iemail);
	select 0 as error;
end$$


drop procedure if exists edit_Lawyers$$
create procedure edit_Lawyers(
	in iID integer,
	in ilawyerNumber  integer unsigned,
	in iname varchar(30),
	in isurnames varchar(40),
	in iaddress varchar (35),
	in iemail varchar(20)
)
begin
	update Lawyers set lawyerNumber=ilawyerNumber,name=iname,surnames=isurnames,address=iaddress,email=iemail	where ID=iID;
	select 0 as error;
end$$

drop procedure if exists delete_Lawyers$$
create procedure delete_Lawyers(
	in iID integer
)
begin
	delete from SuperType where ID = iID;
	select 0 as error;
end$$

-- #######################################################################################
-- ##########################	       	Procuradores			##########################
-- #######################################################################################

drop procedure if exists new_Attorneys$$
create procedure new_Attorneys(
	in iattorneyNumber integer unsigned,
	in iname varchar(30),
	in isurnames varchar(40),
	in iaddress varchar (35),
	in iemail varchar(20)
)
begin
	declare iID integer;
	insert into SuperType() values ();
	SELECT LAST_INSERT_ID() into iID;
	
	insert into Attorneys(ID,attorneyNumber,name,surnames,address,email)
				 values(iID,iattorneyNumber,iname,isurnames,iaddress,iemail);
	select 0 as error;
end$$

drop procedure if exists edit_Attorneys$$
create procedure edit_Attorneys(
	in iID integer,
	in iattorneyNumber integer unsigned,
	in iname varchar(30),
	in isurnames varchar(40),
	in iaddress varchar (35),
	in iemail varchar(20)
)
begin
	update Attorneys set attorneyNumber = iattorneyNumber,name=iname,surnames=isurnames,address=iaddress,email=iemail	where ID=iID;
	select 0 as error;
end$$


drop procedure if exists delete_Attorneys$$
create procedure delete_Attorneys(
	in iID integer
)
begin
	delete from SuperType where ID = iID;
	select 0 as error;
end$$

-- #######################################################################################
-- ##########################	       	  Clientes  			##########################
-- #######################################################################################

drop procedure if exists new_Clients$$
create procedure new_Clients(
	in iDNI char(9),
	in iname varchar(30),
	in isurnames varchar(40),
	in iaddress varchar (35),
	in iemail varchar(20)
)
begin
	declare iID integer;
	insert into SuperType() values ();
	SELECT LAST_INSERT_ID() into iID;
	
	insert into Clients(ID,DNI,name,surnames,address,email)
				 values(iID,iDNI,iname,isurnames,iaddress,iemail);
	select 0 as error;
end$$

drop procedure if exists edit_Clients$$
create procedure edit_Clients(
	in iID integer,
	in iDNI char(9),
	in iname varchar(30),
	in isurnames varchar(40),
	in iaddress varchar (35),
	in iemail varchar(20)
)
begin
	update Clients set DNI = iDNI,name=iname,surnames=isurnames ,address=iaddress,email=iemail	where ID=iID;
	select 0 as error;
end$$

drop procedure if exists delete_Clients$$
create procedure delete_Clients(
	in iID integer
)
begin
	delete from SuperType where ID = iID;
	select 0 as error;
end$$

delimiter ;