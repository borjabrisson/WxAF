delimiter $$

-- ###############################################################################
-- ##########################	        Notas			##########################
-- ###############################################################################

-- select * from notebook where dateNote >= concat(date_format(curdate(),'%Y-%m'),-1) and dateNote <= last_day(curdate());

-- # Revisamos si existe el juicio/procedimiento ¿?: Hay que mirar si la captura del error es lo suficientemente buena.
-- # De no ser así se tendrá que capturar para mostrar el mensaje. 
-- # El owner ya no debería existir ya que pertenecen a la BD del usuario
drop procedure if exists new_note$$
create procedure new_note(
	in idateNote date,
	in itimeNote time,
	in idescription varchar(50),
	in idaysToNotify integer,
	in ijudgmentCode varchar(20)
)
begin
-- 	insert into notebook(dateNote,timeNote,description,daysToNotify,judProced,owner)	values(idateNote,itimeNote,idescription,idaysToNotify,ijudProced,substring_index(user(),'@',1));
	insert into notebook(dateNote,timeNote,description,daysToNotify,judgmentCode)values(idateNote,itimeNote,idescription,idaysToNotify,ijudgmentCode);
	select 0 as error;
end$$

drop procedure if exists edit_note$$
create procedure edit_note(
	in inoteID integer,
	in idateNote date,
	in itimeNote time,
	in idescription varchar(50),
	in idaysToNotify integer,
	in ijudgmentCode varchar(20)
)
begin
	update notebook set dateNote=idateNote,timeNote=itimeNote,description=idescription,daysToNotify=idaysToNotify,judgmentCode=ijudgmentCode where noteID=inoteID;
	select 0 as error;
end$$

drop procedure if exists delete_note$$
create procedure delete_note(
	in inoteID integer
)
begin
	delete from notebook  where noteID=inoteID;
	select 0 as error;
end$$


-- ###############################################################################################
-- ##########################	        Comentarios/Anotaciones			##########################
-- ###############################################################################################

-- 	# Podriamos mirar si existe el noteID en la tabla. Solo para capturar el caso xk el FK nos asegura eso.
drop procedure if exists add_commentNote$$
create procedure add_commentNote(
	in inoteID integer,
	in icommentNote varchar(120)
)
begin
	insert into comment_Note(noteID,commentNote) values(inoteID,icommentNote);
	select 0 as error;
end$$


drop procedure if exists delete_commentNote$$
create procedure delete_commentNote(
	in icommentID integer
)
begin
	delete from comment_Note where commentID=icommentID;
	select 0 as error;
end$$


drop procedure if exists edit_commentNote$$
create procedure edit_commentNote(
	in icommentID integer,
	in icommentNote varchar(120)
)
begin
	update comment_Note set commentNote = icommentNote where commentID=icommentID;
	select 0 as error;
end$$


delimiter ;