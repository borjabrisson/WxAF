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
-- Podriamos mirar si existe el usuario en la tabla user. Solo para capturar el caso xk el FK nos asegura eso.
	declare lasMessage integer;
	insert into message(owner,subject,content,dateSend,timeSend,attached)	values(substring_index(user(),'@',1),isubject,icontent,curdate(),curtime(),iattached);
	SELECT LAST_INSERT_ID() into lasMessage;

	insert into notify_Message(messageID,receiver,state) values (lasMessage,ireceiver,'no-notify');	
	select 0 as error;
end$$


drop procedure if exists reply_message$$
create procedure reply_message(
	in isubject varchar(150),
	in icontent varchar(600),
	in iattached boolean, -- De momento será booleanos. Podria ser un ID varchar y en el caso que sea null representa el otro caso.
	in ireceiver varchar(20),
	in ireplyID integer
)
begin
-- Podriamos mirar si existe el usuario en la tabla user. Solo para capturar el caso xk el FK nos asegura eso.
	declare lasMessage integer;
	insert into message(owner,subject,content,dateSend,timeSend,attached,messageResponse)	values(substring_index(user(),'@',1),isubject,icontent,curdate(),curtime(),iattached,ireplyID);
	SELECT LAST_INSERT_ID() into lasMessage;

	insert into notify_Message(messageID,receiver,state) values (lasMessage,ireceiver,'no-notify');
	select 0 as error;
end$$


drop procedure if exists delete_message$$
create procedure delete_message(
	in imessageID integer
)
begin
-- Podriamos mirar si existe el usuario en la tabla user. Solo para capturar el caso xk el FK nos asegura eso.
	declare existMessage integer;
	declare existReceiver integer;
	
	select messageID into existMessage from message where messageID = imessageID and owner = substring_index(user(),'@',1);
		
	if existMessage is null then -- Este caso no permitiría (no funcionaría) si le enviamos el mismo mensaje varias veces a la misma persona.
		delete from notify_Message where messageID = imessageID and receiver = substring_index(user(),'@',1);
	else
		update message set deletedByUser = true where messageID = imessageID;
	end if;

	select messageID into existMessage from message where messageID = imessageID and deletedByUser = false;
	select count(notifyID) into existReceiver from notify_Message where messageID = imessageID group by messageID;

	if (existMessage is null) and (existReceiver is null ) then
		delete from message where messageID = imessageID;
	end if;
	
	select 0 as error;
end$$




drop procedure if exists forward_message$$ -- Equivalente a new.
create procedure forward_message(
	in inoteID integer,
	in icommentNote varchar(120)
)
begin
end$$

drop procedure if exists read_message$$
create procedure read_message(
	in imessageID integer,
	in inotifyID integer
)
begin
-- 	 Podriamos mirar si existe el noteID en la tabla. Solo para capturar el caso xk el FK nos asegura eso.
	update notify_Message set state = 'read' where messageID = imessageID and notifyID = inotifyID;
	select 0 as error;
end$$

delimiter ;