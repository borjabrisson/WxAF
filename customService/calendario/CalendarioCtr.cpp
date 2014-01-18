#include "CalendarioCtr.h"
calendarioCtr::calendarioCtr() :
		ctrBase() {
}

calendarioCtr::~calendarioCtr() {
}

Customcomunicate calendarioCtr::HandleActions(Customcomunicate block) {
	Customcomunicate msg;
	int result = -1;
	string query;
	switch (block.actionID) {
	case ACT_newNote:
		query = "new_note('" + (*block.data)["dateNote"] + "','"
				+ (*block.data)["timeNote"] + "','" + (*block.data)["description"]
				+ "','" + (*block.data)["daysToNotify"] + "',null)";
		result = this->conector->procedure(this->conector->getUserDB(), query);
		break;

	case ACT_editNote:
		query = "edit_note('" + (*block.data)["noteID"] + "','"
				+ (*block.data)["dateNote"] + "','" + (*block.data)["timeNote"]
				+ "','" + (*block.data)["description"] + "','"
				+ (*block.data)["daysToNotify"] + "',null)";
		result = this->conector->procedure(this->conector->getUserDB(), query);
		break;
	case ACT_delNote:
		query = "delete_note('" + (*block.data)["noteID"] + "')";
		result = this->conector->procedure(this->conector->getUserDB(), query);
		break;
	case ACT_addComment:
		break;
	case ACT_editComment:
		break;
	case ACT_delComment:
		break;
	}
	if (result == 0) {
		msg.actionID = C2V_actionOK;
		//msg.data = ; // Indicamos el mensaje a mostrar.
	} else {
		if (result == -1) {
			msg.actionID = C2V_actionDeny;
			//msg.data = ; // Indicamos el mensaje a mostrar.
		} else {
			msg.actionID = C2V_actionDeny;
			//msg.data = ; // Indicamos el mensaje a mostrar.
		}
	}
	return msg;
}

Customcomunicate calendarioCtr::HandleFilter(Customcomunicate block) {
	Customcomunicate msg;
	return msg;
}

Customcomunicate calendarioCtr::HandleQuery(Customcomunicate block) {
	Customcomunicate msg;
	list<field_type> *dataset = new list<field_type>;
	map<string, string> filter = (*block.data);
	string query;
	switch (block.actionID) {
	case query_note:
		msg.specificAction =type_noteList;
		query =
				"select day(dateNote) as dayNote from notebook where dateNote >= concat(date_format('"
						+ filter["dateNote"]
						+ "','%Y-%m'),-1) and dateNote <= last_day('"
						+ filter["dateNote"] + "')";
		break;
	case query_dataset:
		msg.specificAction =type_dataList;
		query =
				"select noteID,dateNote,timeNote,description,DATEDIFF(dateNote,'"
						+ filter["dateNote"]
						+ "')as daysToNotify from notebook where date_sub(dateNote,interval daysToNotify DAY) <= '"
						+ filter["dateNote"] + "' and dateNote>='"
						+ filter["dateNote"] + "' order by dateNote ASC";
		break;
	}
	this->conector->query(this->conector->getUserDB(), query, *dataset);
	msg.actionID = C2V_showList;
	msg.dataset = dataset;

	return msg;
}
