#include "CalendarioPage.h"

CalendarioPage::CalendarioPage(wxWindow *parent, string id) :
		panelCalendar(parent, id) {
	panelCalendar::Init();
}

void CalendarioPage::Reload() {
	this->loadNoteMark();
	this->loadNoteList();
}

void CalendarioPage::OnLoad() {
	this->addAction(ACT_newNote, "Nueva Nota");
	this->addAction(ACT_editNote, "Editar Nota");
	this->addAction(ACT_delNote, "Eliminar Nota");
}

void CalendarioPage::actionsHandler(int action) {
	switch (action) {
	case ACT_newNote: {
		CalendarioCard* pop = new CalendarioCard;
		pop->BuildPop(this);
		break;
	}
	case ACT_editNote: {
		if (checkSelectedRowsNumber()) {
			wxArrayInt rows = this->grid->GetSelectedRows();
			this->curItem = this->noteList->MygetRow(rows[0]);
			cout << "seleccionado " << this->curItem["noteID"] << endl;

			CalendarioCard* pop = new CalendarioCard;
			pop->BuildPop(this);
			pop->setValues(this->curItem);
		}
		break;
	}
	case ACT_delNote: {
		if (checkSelectedRowsNumber()) {
			wxArrayInt rows = this->noteList->GetSelectedRows();
			this->curItem = this->noteList->MygetRow(rows[0]);

			map<string, string> *data = new map<string, string>;
			(*data)["noteID"] = this->curItem["noteID"];
			//	this->completeActionsHandler(*data);
			Customcomunicate block = this->sendAction2(ACT_delNote, data);
			this->handleMessage(block);
		}
		break;
	}
	case 4:
		break;
	default:
		cout << "default" << endl;
		break;
	}

}

void CalendarioPage::completeActionsHandler(map<string, string> data) {
// 	if(this->sendAction(this->curAction,data,data)) this->Reload();
// 	else{
// 		this->showMessage("Error",this->getMsgError());
// 	}
	map<string, string> *datas = new map<string, string>;
	*datas = data;
	Customcomunicate block = this->sendAction2(this->curAction, datas);
	this->handleMessage(block);
//	if (datas != NULL) delete datas;
}

void CalendarioPage::buildQuery() {
// 	this->qry addField(string table, string field);
}

list<itemHeaderColumn> CalendarioPage::headerGrid() {
	list<itemHeaderColumn> header;
	header.push_back(itemHeaderColumn("noteID", "ID"));
	header.push_back(itemHeaderColumn("dateNote", "Fecha"));
	header.push_back(itemHeaderColumn("timeNote", "Hora"));
	header.push_back(itemHeaderColumn("description", "Descripcion"));
	header.push_back(itemHeaderColumn("daysToNotify", "Dias Restantes"));
// 	header.push_back(itemHeaderColumn("judProced","Procedimiento"));
	header.push_back(itemHeaderColumn("owner", "Propietario"));

	return header;
}

// void CalendarioPage::OnSel_Changed(wxDateTime date){}
void CalendarioPage::OnDoubleClicked(wxDateTime date) {
	this->curDate = date;
	push_Debug("CalendarioPage::OnDoubleClicked:");

}

void CalendarioPage::OnYear_Changed(wxDateTime date) {
	this->curDate = date;
	push_Debug("CalendarioPage::OnYear_Changed:");
	this->Reload();
}

void CalendarioPage::OnMonth_Changed(wxDateTime date) {
	this->curDate = date;
	push_Debug("CalendarioPage::OnMonth_Changed:");

	this->Reload();
}
void CalendarioPage::OnDay_Changed(wxDateTime date) {
	push_Debug("CalendarioPage::OnDay_Changed:");
	this->curDate = date;

	this->Reload();
}

void CalendarioPage::loadNoteMark() {
	push_Debug("CalendarioPage::loadNoteMark:");
	list<field_type>::iterator it;
	map<string, string> *filter = new map<string, string>;
	(*filter)["dateNote"] = wxDateToString(this->curDate);

	Customcomunicate block = this->sendQuery(query_note, filter);
	this->handleMessage(block);
}

void CalendarioPage::loadNoteList() {
	push_Debug("CalendarioPage::loadNoteList:");
	this->noteList->resetData();
	map<string, string> *filter = new map<string, string>;
	(*filter)["dateNote"] = wxDateToString(this->curDate);

	Customcomunicate block = this->sendQuery(query_dataset, filter);
	this->handleMessage(block);
}

void CalendarioPage::showList(Customcomunicate& block) {
	cout << "CalendarioPage::ShowList" << endl;
	cout << "CalendarioPage::ShowList tipo " <<block.specificAction << endl;
	list<field_type>::iterator it;
	switch (block.specificAction) {
	case type_noteList:
		for (it = block.dataset->begin(); it != block.dataset->end(); it++) {
			this->addNotes(strToint((*it)["dayNote"]));
		}
		break;
	case type_dataList:
		int ind = 0;
		this->noteList->pushDataSet(*block.dataset);
		for (it = block.dataset->begin(); it != block.dataset->end();
				ind++, it++) {
			if ((*it)["daysToNotify"] == "0") {
				this->noteList->setColourRow(ind, wxColour(135, 206, 235)); //sky blue
			}
		}
		break;
	}
}

