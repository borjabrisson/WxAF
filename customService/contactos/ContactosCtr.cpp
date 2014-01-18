#include "ContactosCtr.h"
ContactosCtr::ContactosCtr() :
		ctrBase() {
}

ContactosCtr::~ContactosCtr() {
}

Customcomunicate ContactosCtr::HandleActions(Customcomunicate block) {
	Customcomunicate msg;
	switch (block.specificAction) {
	case type_Empresas:
		return this->HandleCompanyActions(block);
		break;
	case type_Abogados:
		return this->HandleLawyerActions(block);
		break;
	case type_Procuradores:
		return this->HandleAttorneyActions(block);
		break;
	case type_Clientes:
		return this->HandleContactActions(block);
		break;
	}
	return msg;
}

Customcomunicate ContactosCtr::HandleFilter(Customcomunicate block) {
	Customcomunicate msg;
	return msg;
}

Customcomunicate ContactosCtr::HandleQuery(Customcomunicate block) {
	Customcomunicate msg;
	list<field_type> *dataset = new list<field_type>;
	string query;
	switch (block.actionID) {
	case type_Empresas:
		query =
				"select ID,CIF,CIF as identify,name,web,address,email from Company";
		break;
	case type_Abogados:
		query =
				"select ID,lawyerNumber,lawyerNumber as identify,name,surnames,address,email from Lawyers limit 1";
		break;
	case type_Procuradores:
		query =
				"select ID,attorneyNumber,attorneyNumber as identify,name,surnames,address,email from Attorneys";
		break;
	case type_Clientes:
		query =
				"select ID,DNI,DNI as identify,name,surnames,address,email from Clients";
		break;
	}
	this->conector->query(this->conector->getUserDB(), query, *dataset);
	msg.actionID = C2V_showList;
	msg.dataset = dataset;
	return msg;
}

Customcomunicate ContactosCtr::HandleContactActions(Customcomunicate &block) {
	Customcomunicate msg;
	int result = -1;
	switch (block.actionID) {
	case ACT_newContact: {
		string args[] = { "DNI","name", "surnames","address", "email", };
		string argsString = this->buildArgsString(args, 5, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"new_Client(" + argsString + ")" );
		break;
	}
	case ACT_editContact: {
		string args[] = { "ID","DNI","name", "surnames","address", "email", };
		string argsString = this->buildArgsString(args, 6, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"edit_Client(" + argsString + ")" );
	}
		break;
	case ACT_deleteContact: {
		string args[] = { "ID" };
		string argsString = this->buildArgsString(args, 1, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"delete_Client(" + argsString + ")" );
		break;
	}
	}
	if (result == 0){
		msg.actionID = C2V_actionOK;
	}
	else{
		msg.actionID = C2V_actionDeny;
	}
	return msg;
}

Customcomunicate ContactosCtr::HandleCompanyActions(Customcomunicate &block) {
	Customcomunicate msg;
	int result = -1;
	switch (block.actionID) {
	case ACT_newContact: {
		string args[] = { "name", "address", "email", "CIF", "web", "contact" };
		string argsString = this->buildArgsString(args, 6, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"new_Company(" + argsString + ")" );
		break;
	}
	case ACT_editContact: {
		string args[] = { "ID", "name", "address", "email", "CIF", "web",
				"contact" };
		string argsString = this->buildArgsString(args, 7, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"edit_Company(" + argsString + ")" );
	}
		break;
	case ACT_deleteContact: {
		string args[] = { "ID" };
		string argsString = this->buildArgsString(args, 1, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"delete_Company(" + argsString + ")" );
		break;
	}
	}
	if (result == 0){
		msg.actionID = C2V_actionOK;
	}
	else{
		msg.actionID = C2V_actionDeny;
	}
	if (result == 0){
		msg.actionID = C2V_actionOK;
	}
	else{
		msg.actionID = C2V_actionDeny;
	}
	return msg;
}

Customcomunicate ContactosCtr::HandleLawyerActions(Customcomunicate &block) {
	Customcomunicate msg;
	int result = -1;
	switch (block.actionID) {
	case ACT_newContact: {
		string args[] = { "lawyerNumber","name", "surnames","address", "email", };
		string argsString = this->buildArgsString(args, 5, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"new_Lawyers(" + argsString + ")" );
		break;
	}
	case ACT_editContact: {
		string args[] = { "ID","lawyerNumber","name", "surnames","address", "email", };
		string argsString = this->buildArgsString(args, 6, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"edit_Lawyers(" + argsString + ")" );
	}
		break;
	case ACT_deleteContact: {
		string args[] = { "ID" };
		string argsString = this->buildArgsString(args, 1, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"delete_Lawyers(" + argsString + ")" );
		break;
	}
	}
	if (result == 0){
		msg.actionID = C2V_actionOK;
	}
	else{
		msg.actionID = C2V_actionDeny;
	}
	return msg;
}

Customcomunicate ContactosCtr::HandleAttorneyActions(Customcomunicate &block) {
	Customcomunicate msg;
	int result = -1;
	switch (block.actionID) {
	case ACT_newContact: {
		string args[] = { "attorneyNumber","name", "surnames","address", "email", };
		string argsString = this->buildArgsString(args, 5, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"new_Attorneys(" + argsString + ")" );
		break;
	}
	case ACT_editContact: {
		string args[] = { "ID","attorneyNumber","name", "surnames","address", "email", };
		string argsString = this->buildArgsString(args, 6, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"edit_Attorneys(" + argsString + ")" );
	}
		break;
	case ACT_deleteContact: {
		string args[] = { "ID" };
		string argsString = this->buildArgsString(args, 1, *block.data);
		result = this->conector->procedure(this->conector->getUserDB(),
				"delete_Attorneys(" + argsString + ")" );
		break;
	}
	}
	if (result == 0){
		msg.actionID = C2V_actionOK;
	}
	else{
		msg.actionID = C2V_actionDeny;
	}
	return msg;
}

bool ContactosCtr::sendAction(string idFrame, int action,
		map<string, string> data, map<string, string> key) {

	cout << "ContactosCtr::sendAction.# idFrame: " + idFrame + ". Action: "
			<< action << endl;
	bool ret = false;
//	string clause;
//	data["attached"] = "false";
//	switch(action){
//		case ACT_newMessage:
//		case ACT_Forwards:
//			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
//			break;
//		case ACT_Replay:
//			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
//			break;
//		case ACT_delMessage:
//			clause = "delete_message('"+data["messageID"]+"')";
//			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
//			break;
//		case ACT_readMessage:
//			ret = this->conector->procedure(this->conector->getGeneralDB(),clause);
//			break;
//		default:
//			break;
//	}
	return ret;
}
