delimiter $$
select "Files SP" as step$$

-- #######################################################################################
-- ##########################	        Configuracion			##########################
-- #######################################################################################

drop procedure if exists set_Comfiguration$$
create procedure set_Comfiguration(
	in ifileNumber integer unsigned,
	in iprefix varchar(6), -- Contenido previo a la fecha (con formato)
	in ilastDate varchar(10), -- Indica la ultima fecha usada, indicando a partir de cual se resetea.
	in iformatDate varchar(6), -- Formato utilizado para mostrar la fecha.
	in iperiodReset varchar (6), -- Indica el formato a utilizar para crear la fecha de reseteo. Si es por año, por trimestre, combinaciones, etc.
	in idivisor varchar(4)  -- Separa la fecha formateada del numero de expediente.
)
begin
	update Configuration set fileNumber=ifileNumber,prefix=iprefix,lastDate=ilastDate,
							 formatDate=iformatDate,periodReset=iperiodReset,divisor=idivisor where ID=1;
	select 0 as error;
end$$


DROP FUNCTION IF EXISTS nextFileNumber$$
create function nextFileNumber()
returns varchar(20)
DETERMINISTIC
begin
    declare iprefix varchar(5);
    declare iformatDate varchar(6);
    declare iperiodReset varchar(6);
    declare ireset varchar(10);
    declare idivisor varchar(4);

    declare iserial varchar(16);
    declare icounter integer unsigned;

    select prefix,formatDate,divisor,periodReset into iprefix,iformatDate,idivisor,iperiodReset from Configuration where ID = 1;
    select date_format(CURDATE(),iperiodReset) into ireset;

    select fileNumber into icounter from Configuration where ID = 1 and lastDate = ireset;
    if icounter is null then -- No posee este valor por lo que hemos sobrepasado la última marca de reset.
		update Configuration set fileNumber=1, lastDate = ireset where ID=1;
		set icounter = 1;
    else
		update Configuration set fileNumber=fileNumber+1 where ID=1;
		set icounter=icounter+1;
    end if;

    select concat(iprefix,date_format(CURDATE(),iformatDate),idivisor,lpad(icounter,5,'0')) into iserial;

    return iserial;
end$$

-- #######################################################################################
-- ##########################	        Expedientes				##########################
-- #######################################################################################
drop procedure if exists new_File$$
create procedure new_File( -- Antencion: El fileCode si es null se debe crear
	in ifileCode varchar(16),
	in iopenDate date,
	in icloseDate date,
	in iclientCode integer unsigned,
	in iobservation varchar(120)
)
begin
	if ifileCode is null then
		select nextFileNumber() into ifileCode;
	end if;
	insert into Files (fileCode,openDate,closeDate,clientCode,observation) values (ifileCode,iopenDate,null,iclientCode,iobservation);
	select 0 as error;
end$$

drop procedure if exists edit_File$$
create procedure edit_File(
	in ifileCode varchar(16),
	in iopenDate date,
	in icloseDate date,
	in iclientCode integer unsigned,
	in iobservation varchar(120),
	in iLastFileCode varchar(16)
)
begin
	update Files set fileCode=ifileCode,openDate=iopenDate,closeDate=icloseDate,clientCode=iclientCode,observation=iobservation where fileCode=iLastFileCode;
	select 0 as error;
end$$

drop procedure if exists delete_File$$
create procedure delete_File(
	in ifileCode varchar(16)
)
begin
	delete from Files where fileCode=ifileCode;
	select 0 as error;
end$$


drop procedure if exists close_File$$
create procedure close_File(
	in ifileCode varchar(16)
)
begin
	update Files set closeDate=CURDATE() where fileCode=ifileCode;
	select 0 as error;
end$$

-- #######################################################################################
-- ##########################	        Procedimientos			##########################
-- #######################################################################################

-- @ Revisamos que existan los distintos FK?
-- @ Sería interesante el gestionar que el tipo de procedimiento pueda realizarse en el juzgado indicado. (Necesitariamos una tabla para relacionar tipos.)
-- @ Gestionamos el cierre del caso (expediente) y/o procedimiento.

drop procedure if exists new_Judgment$$
create procedure new_Judgment(
	in ijudgmentCode varchar(16),
	in ifileCode varchar(16),
	in istartDate date,
	in ijudgmentType varchar(10),
	in icourts integer unsigned,
	in inextEventDate date,
	in inextEventHour time, -- En el mismo registro???
	in iobservations varchar(500)
)
begin
	insert into Judgments (judgmentCode,fileCode,startDate,judgmentType,courts,nextEventDate,nextEventHour,observations,closeDate)
				   values (ijudgmentCode,ifileCode,istartDate,ijudgmentType,icourts,inextEventDate,inextEventHour,iobservations,null);
	select 0 as error;
end$$
	
drop procedure if exists edit_Judgment$$
create procedure edit_Judgment(
	in ijudgmentCode varchar(16),
	in ifileCode varchar(16),
	in istartDate date,
	in icloseDate date,
	in ijudgmentType varchar(10),
	in icourts integer unsigned,
	in inextEventDate date,
	in inextEventHour time, -- En el mismo registro???
	in iobservations varchar(500),
	in OldjudgmentCode varchar(16)
)
begin
	update Judgments set judgmentCode=ijudgmentCode,fileCode=ifileCode,startDate=startDate,closeDate=icloseDate,
		judgmentType=ijudgmentType,courts=icourts,nextEventDate=inextEventDate,nextEventHour=inextEventHour,observations=iobservations
		where 	judgmentCode=OldjudgmentCode;
	select 0 as error;
end$$	

drop procedure if exists delete_Judgment$$
create procedure delete_Judgment(
	in ijudgmentCode varchar(16)
)
begin
	delete from  Judgments where judgmentCode=ijudgmentCode;
	select 0 as error;
end$$	
	
	
--	// close
drop procedure if exists close_Judgment$$
create procedure close_Judgment(
	in ijudgmentCode varchar(16)
)
begin
	update Judgments set closeDate=CURDATE() where judgmentCode=ijudgmentCode;
	select 0 as error;
end$$

-- Creamos un nuevo procedimiento, asociandolo al Proc previo
drop procedure if exists add_appeal_Judgment$$
create procedure add_appeal_Judgment(
	in ijudgmentCode varchar(16),
	in iappealCode varchar(16), -- Codigo del recurso/apelacion
	in ifileCode varchar(16),
	in istartDate date,
	in ijudgmentType varchar(10),
	in icourts integer unsigned,
	in inextEventDate date,
	in inextEventHour time, -- En el mismo registro???
	in iobservations varchar(500)
)
begin
	insert into Judgments (judgmentCode,fileCode,startDate,judgmentType,courts,nextEventDate,nextEventHour,observations,closeDate)
		   values (iappealCode,ifileCode,istartDate,ijudgmentType,icourts,inextEventDate,inextEventHour,iobservations,null);
	update Judgments set appealCode=iappealCode where judgmentCode=ijudgmentCode;
	select 0 as error;
end$$


--	 Le asociamos un Proc. existente como recurso.
drop procedure if exists associate_appeal_Judgment$$
create procedure associate_appeal_Judgment(
	in ijudgmentCode varchar(16),
	in iappealCode varchar(16) -- Codigo del recurso/apelacion
)
begin
	update Judgments set appealCode=iappealCode where judgmentCode=ijudgmentCode;
	select 0 as error;
end$$
	
	

-- #######################################################################################
-- ##########################	        Escritos				##########################
-- #######################################################################################
drop procedure if exists new_typeWrits$$
create procedure new_typeWrits(
	in itype varchar(10),
	in idescription varchar(20)
)
begin
	insert into type_writs(type,description)values(itype,idescription);
	select 0 as error;
end$$

drop procedure if exists edit_typeWrits$$
create procedure edit_typeWrits(
	in itype varchar(10),
	in idescription varchar(20),
	in iLastType varchar(10)
)
begin
	update type_writs set type=itype, description=idescription where type=iLastType;
	select 0 as error;
end$$

drop procedure if exists delete_typeWrits$$
create procedure delete_typeWrits(
	in itype varchar(10)
)
begin
	delete from  type_writs where type = itype;
	select 0 as error;
end$$

drop procedure if exists new_associatedDocuments$$
create procedure new_associatedDocuments(
	in ijudgmentCode varchar(16),
	in itype varchar(10),
	in iDocument varchar(40),
	in iname varchar(20),
	in iexpirationDate Date
)
begin
	insert into associatedDocuments (judgmentCode,type,Document,name,expirationDate,creationDate,modifyDate)
							values(ijudgmentCode,itype,iDocument,iname,iexpirationDate,CURDATE(),CURDATE());
	select 0 as error;
end$$

drop procedure if exists edit_associatedDocuments$$
create procedure edit_associatedDocuments(
	in idocumentCode integer unsigned,
	in ijudgmentCode varchar(16),
	in itype varchar(10),
	in iDocument varchar(40),
	in iname varchar(20),
	in iexpirationDate Date
)
begin
	update associatedDocuments set judgmentCode=ijudgmentCode,type=itype,Document=iDocument,
									name=iname,expirationDate=iexpirationDate,modifyDate=CURDATE() where documentCode=idocumentCode;
	select 0 as error;
end$$
	
drop procedure if exists delete_associatedDocuments$$
create procedure delete_associatedDocuments(
	in idocumentCode integer unsigned
)
begin
	delete from  associatedDocuments where documentCode = idocumentCode;
	select 0 as error;
end$$

-- #######################################################################################
-- ##########################	   Contrarios y Defendidos		##########################
-- #######################################################################################

-- @ Se deberia mirar si esa tupla no está vacía. Y si no se repite en la defensa. DONE:OK
-- #! Tb que no se repiten el registro? Ej: Que el cliente no se repita. DONE:Garantizado por SQL. ¿Lo capturamos?
--  Que es mejor? Dejar editar o eliminar el registro y crear uno nuevo para cada cambio.¿?
-- @! Los capturamos nosotros? o dejamos que se lance la excepcion SQL¿?¿?

drop procedure if exists add_Opposite$$
create procedure add_Opposite(
	in ijudgmentCode varchar(16),
	in ioppositeClient_Code  integer unsigned ,
	in ioppositeCounsel_Code integer unsigned ,
	in ioppositeAttorney_Code integer unsigned 
)
begin
	declare icount integer unsigned;
	select judgmentCode into icount from Defense where judgmentCode=ijudgmentCode and (defenseAttorney_Code=ioppositeAttorney_Code or
																		defenseClient_Code=ioppositeClient_Code  or defenseCounsel_Code=ioppositeCounsel_Code);

	if icount is null then
		insert into Opposite(judgmentCode,oppositeClient_Code,oppositeCounsel_Code,oppositeAttorney_Code)
					values(ijudgmentCode,ioppositeClient_Code,ioppositeCounsel_Code,ioppositeAttorney_Code);
		select 0 as error;
	else
		select 1 as error, "Se ha intentado introducir algún personal de la defensa" as msg;
	end if;
end$$

drop procedure if exists delete_Opposite$$
create procedure delete_Opposite(
	in ijudgmentCode varchar(16),
	in ioppositeClient_Code  integer unsigned ,
	in ioppositeCounsel_Code integer unsigned ,
	in ioppositeAttorney_Code integer unsigned 
)
begin
	delete from Opposite where judgmentCode=ijudgmentCode and oppositeClient_Code=ioppositeClient_Code 
							and oppositeCounsel_Code=ioppositeCounsel_Code	and oppositeAttorney_Code=ioppositeAttorney_Code;
	select 0 as error;
end$$


drop procedure if exists add_Defense$$
create procedure add_Defense(
	in ijudgmentCode varchar(16),
	in idefenseClient_Code  integer unsigned ,
	in idefenseCounsel_Code integer unsigned ,
	in idefenseAttorney_Code integer unsigned 
)
begin
	declare icount integer unsigned;
	select judgmentCode into icount from Opposite where judgmentCode=ijudgmentCode and (oppositeAttorney_Code=idefenseClient_Code or
																		idefenseClient_Code=oppositeClient_Code  or idefenseCounsel_Code=oppositeCounsel_Code);
	if icount is null then
		insert into Defense(judgmentCode,defenseClient_Code,defenseCounsel_Code,defenseAttorney_Code)
				 values(ijudgmentCode,idefenseClient_Code,idefenseCounsel_Code,idefenseAttorney_Code);
		select 0 as error;
	else
		select 1 as error, "Se ha intentado introducir algún personal del contrario" as msg;
	end if;
	
end$$

drop procedure if exists delete_Defense$$
create procedure delete_Defense(
	in ijudgmentCode varchar(16),
	in idefenseClient_Code  integer unsigned ,
	in idefenseCounsel_Code integer unsigned ,
	in idefenseAttorney_Code integer unsigned 
)
begin
	delete from Defense where judgmentCode=ijudgmentCode and defenseClient_Code=idefenseClient_Code 
							and defenseCounsel_Code=idefenseCounsel_Code	and defenseAttorney_Code=idefenseAttorney_Code;
	select 0 as error;
end$$

delimiter ;