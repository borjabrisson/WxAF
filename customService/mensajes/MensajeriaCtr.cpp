#include "MensajeriaCtr.h"
MensajeriaCtr::MensajeriaCtr() : ctrBase() {
}

MensajeriaCtr::~MensajeriaCtr(){
}

Customcomunicate MensajeriaCtr::HandleActions(Customcomunicate block) {
	Customcomunicate msg;
	return msg;
}
Customcomunicate MensajeriaCtr::HandleFilter(Customcomunicate block) {
	Customcomunicate msg;
	return msg;
}

Customcomunicate MensajeriaCtr::HandleQuery(Customcomunicate block) {
	Customcomunicate msg;
	list<field_type> *dataset = new list<field_type>;
	string query;
//	switch (block.actionID){
//		case type_Empresas:
//			query = "select ID,CIF,CIF as identify,name,web,address,email from Company";
//			break;
//		case type_Abogados:
//			query = "select ID,lawyerNumber,lawyerNumber as identify,name,surnames,address,email from Lawyers limit 1";
//				break;
//		case type_Procuradores:
//			query = "select ID,attorneyNumber,attorneyNumber as identify,name,surnames,address,email from Attorneys";
//				break;
//		case type_Clientes:
//			query = "select ID,DNI,DNI as identify,name,surnames,address,email from Clients";
//				break;
//		}
	this->conector->query(this->conector->getUserDB(),query,*dataset);
	msg.actionID = C2V_showList;
	msg.dataset = dataset;
	return msg;
}


bool MensajeriaCtr::sendAction(string idFrame,int action, map<string,string> data, map<string,string> key){
// 	push_Debug("MensajeriaCtr::sendAction.# idFrame: "+idFrame+". Action: "+action);

	cout << "MensajeriaCtr::sendAction.# idFrame: "+idFrame+". Action: "<<action << endl;
// 	map<string,string>::iterator it;
// 	for (it=data.begin(); it != data.end();it++){
// 		cout << "Campo: "<< (*it).first << ".   Valor: "<< (*it).second << endl;
// 	}
// 	return true;
	bool ret=false;
	string clause;
	data["attached"] = "false";
	switch(action){
		case ACT_newMessage:
		case ACT_Forwards:
			clause = "new_message('"+data["subject"]+"','"+data["content"]+"','"+data["attached"]+"','"+data["receiver"]+"')";
			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
			break;
		/*
			clause = "fordward_message('"+data["subject"]+"','"+data["content"]+"','"+data["dateSend"]+"','"+data["timeSend"]+"','"+data["attached"]+"','"+data["receiver"]+"','"+data["replyID"]+"')";
			ret = this->conector->procedure("agosal",clause);
			break;*/
		case ACT_Replay:
			clause = "reply_message('"+data["subject"]+"','"+data["content"]+"','"+data["attached"]+"','"+data["receiver"]+"','"+data["messageID"]+"')";
			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
			break;
		case ACT_delMessage:
			clause = "delete_message('"+data["messageID"]+"')";
			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
			break;
		case ACT_readMessage:
			clause = "read_message('"+data["messageID"]+"','"+data["notifyID"]+"')";
			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
			break;
		default:
			break;
	}
	return ret;

	
// 	return this->conector->procedure("test","call prueba(\"121\",\"554\",\"0\");");
}

list<field_type> MensajeriaCtr::select(string idFrame,int type,map<string,string> filter){
	string query,where = getClauseWhere(filter);
	list<field_type> data;
	switch(type){
		case 0:
			filter["messageID"] = ""; // PArche para las pruebas de filtros. Una vez en funcionamiento no deberia ocurrir.
			where = getClauseWhere(filter);
			query =  "select owner,message.messageID as messageID, subject,notifyID,if(state='no-notify' or state='notify','*','') as state, content from notify_Message inner join message on message.messageID = notify_Message.messageID where receiver=substring_index(user(),'@',1) and state<>'owner' and state<>'deleted'";
			if (where != "")query+= " and " + where;
			this->conector->query(this->conector->getGeneralDB(),query,data);
			break;

		case 1:
			query =  "select content from message where messageID = "+filter["messageID"];
			this->conector->query(this->conector->getGeneralDB(),query,data);
			cout << "Entramos por el 1: "+query << endl;
			break;
	}
	return data;
	
}
