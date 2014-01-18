delimiter $$

-- select owner,message.messageID as message, subject,if(state='no-notify' or state='notify','*','') as state, content from notify_Message inner join message on message.messageID = notify_Message.messageID where receiver=substring_index(user(),'@',1) and state<>'owner' and state<>'deleted';

drop procedure if exists new_message$$
create procedure new_message(
	in isubject varchar(150),
	in icontent varchar(600),
	in iattached boolean, -- De momento será booleanos. Podria ser un ID varchar y en el caso que sea null representa el otro caso.
	in ireceiver varchar(20)
)
begin
	declare existUser varchar(20);
	declare lasMessage integer;
	
	select userID into existUser from Users where userID = ireceiver ;
	if existUSer then
		select 1 as error,"Usuario $_user desconocido." as msg, ireceiver as user;
	else
		insert into message(owner,subject,content,dateSend,timeSend,attached)values(substring_index(user(),'@',1),isubject,icontent,curdate(),curtime(),iattached);
		SELECT LAST_INSERT_ID() into lasMessage;
	
		insert into notify_Message(messageID,receiver,state) values (lasMessage,ireceiver,'no-notify');	
		select 0 as error;
	end if;
end$$

-- Responder
drop procedure if exists reply_message$$
create procedure reply_message(
	in isubject varchar(150),
	in icontent varchar(600),
	in iattached boolean, -- De momento será booleanos. Podria ser un ID varchar y en el caso que sea null representa el otro caso.
	in ireceiver varchar(20),
	in ireplyID integer
)
begin
	declare existUser varchar(20);
	declare lasMessage integer;
	
	select userID into existUser from Users where userID = ireceiver ;
	if existUSer then
		select 1 as error,"Usuario $_user desconocido." as msg, ireceiver as user;
	else
		insert into message(owner,subject,content,dateSend,timeSend,attached,messageResponse)
			values(substring_index(user(),'@',1),isubject,icontent,curdate(),curtime(),iattached,ireplyID);
		SELECT LAST_INSERT_ID() into lasMessage;
	
		insert into notify_Message(messageID,receiver,state) values (lasMessage,ireceiver,'no-notify');
		select 0 as error;
	end if;
end$$


drop procedure if exists delete_message$$
create procedure delete_message(
	in imessageID integer
)
begin
	declare existMessage integer;
	declare existReceiver integer;
	
	select messageID into existMessage from message where messageID = imessageID and owner = substring_index(user(),'@',1);
		
	if existMessage is null then -- Este caso no permitiría (no funcionaría) si le enviamos el mismo mensaje varias veces a la misma persona.
-- 	Fom: Juanito To: pepe,pepe,pepe,pepe. Se borrarian todos-> No permitir repetir usuarios.
		select messageID into existMessage from notify_Message where messageID = imessageID and receiver = substring_index(user(),'@',1);
		if existMessage is null then
			select 1 as error, "Se ha intentado borrar un mensaje que no le pertenece o que ya ha sido borrado." as msg;
		else
			update notify_Message set state = 'deleted' where messageID = imessageID;
--			delete from notify_Message where messageID = imessageID and receiver = substring_index(user(),'@',1);
		end if;
	else
		update message set deletedByUser = true where messageID = imessageID;
	end if;

	select messageID into existMessage from message where messageID = imessageID and deletedByUser = false;
	select messageID into existReceiver from notify_Message where messageID = imessageID  and state <> 'deleted' group by messageID;

	if (existMessage is null) and (existReceiver is null ) then
		delete from message where messageID = imessageID;
		delete from notify_Message where messageID = imessageID;
	end if;
	
	select 0 as error;
end$$

drop procedure if exists read_message$$
create procedure read_message(
	in imessageID integer,
	in inotifyID integer
)
begin
	update notify_Message set state = 'read' where messageID = imessageID and notifyID = inotifyID;
	select 0 as error;
end$$


drop procedure if exists notify_message$$
create procedure notify_message(
	in imessageID integer,
	in inotifyID integer
)
begin
	update notify_Message set state = 'notified' where messageID = imessageID and notifyID = inotifyID;
	select 0 as error;
end$$


delimiter ;