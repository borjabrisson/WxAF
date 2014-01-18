delimiter $$

-- select * from notebook where dateNote >= concat(date_format(curdate(),'%Y-%m'),-1) and dateNote <= last_day(curdate());

drop procedure if exists new_note$$
create procedure new_note(
	in idateNote date,
	in itimeNote time,
	in idescription varchar(50),
	in idaysToNotify integer,
	in ijudProced varchar(20)
)
begin
-- Podriamos mirar si existe el usuario en la tabla user. Solo para capturar el caso xk el FK nos asegura eso.
-- select 1 as error, 'El día ya se encuentra abierto' as message, 'generic_err01' as idMessage, iworkday as workday;

	insert into notebook(dateNote,timeNote,description,daysToNotify,judProced,owner)	values(idateNote,itimeNote,idescription,idaysToNotify,ijudProced,substring_index(user(),'@',1));
	select 0 as error;
end$$


drop procedure if exists edit_note$$
create procedure edit_note(
	in inoteID integer,
	in idateNote date,
	in itimeNote time,
	in idescription varchar(50),
	in idaysToNotify integer,
	in ijudProced varchar(20)
)
begin
-- Podriamos mirar si existe el usuario en la tabla user. Solo para capturar el caso xk el FK nos asegura eso.
-- select 1 as error, 'El día ya se encuentra abierto' as message, 'generic_err01' as idMessage, iworkday as workday;
	update notebook set dateNote=idateNote,timeNote=itimeNote,description=idescription,daysToNotify=idaysToNotify,judProced=ijudProced where noteID=inoteID;
	select 0 as error;
end$$


drop procedure if exists delete_note$$
create procedure delete_note(
	in inoteID integer
)
begin
-- Podriamos mirar si existe el usuario en la tabla user. Solo para capturar el caso xk el FK nos asegura eso.
-- select 1 as error, 'El día ya se encuentra abierto' as message, 'generic_err01' as idMessage, iworkday as workday;
	delete from notebook  where noteID=inoteID;
	select 0 as error;
end$$




drop procedure if exists add_commentNote$$
create procedure add_commentNote(
	in inoteID integer,
	in icommentNote varchar(120)
)
begin
-- 	 Podriamos mirar si existe el noteID en la tabla. Solo para capturar el caso xk el FK nos asegura eso.
	insert into comment_Note(noteID,commentNote) values(inoteID,icommentNote);
	select 0 as error;
end$$


drop procedure if exists delete_commentNote$$
create procedure delete_commentNote(
	in icommentID integer
)
begin
-- 	 Podriamos mirar si existe el noteID en la tabla. Solo para capturar el caso xk el FK nos asegura eso.
	delete from comment_Note where commentID=icommentID;
	select 0 as error;
end$$


drop procedure if exists edit_commentNote$$
create procedure edit_commentNote(
	in icommentID integer,
	in icommentNote varchar(120)
)
begin
-- 	 Podriamos mirar si existe el noteID en la tabla. Solo para capturar el caso xk el FK nos asegura eso.
	update comment_Note set commentNote = icommentNote where commentID=icommentID;
	select 0 as error;
end$$


delimiter ;