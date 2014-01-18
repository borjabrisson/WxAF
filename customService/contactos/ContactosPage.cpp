#include "ContactosPage.h"

ContactosPage::ContactosPage(wxWindow *parent, string id) :
		panelGrid(parent, id) {
	lastItemSelected = type_Empresas;
	this->Init();
}

void ContactosPage::Reload() {
	this->grid->resetGrid();
	this->grid->pushHeaders(getHeaderGrid());
	Customcomunicate block = this->sendQuery(lastItemSelected);
	this->handleMessage(block);
}

void ContactosPage::OnLoad() {
	lastItemSelected = 0;
	wxArrayString array;
	array.Add(_T("Empresas"));
	array.Add(_T("Clientes	"));
	array.Add(_T("Abogados"));
	array.Add(_T("Procuradores"));

	choice = new wxChoice(this, wxNewId(), wxDefaultPosition, wxSize(190, 30),
			array);

	this->Connect(choice->GetId(), wxEVT_COMMAND_CHOICE_SELECTED,
			wxCommandEventHandler(ContactosPage::OnClickChoiseItem));
	this->addAction(ACT_changeTypeContact, choice);

	this->addAction(ACT_viewContact, "Ver Contacto");
	this->addAction(ACT_newContact, "Nuevo Contacto");
	this->addAction(ACT_editContact, "Editar Contacto");
	this->addAction(ACT_deleteContact, "Eliminar Contacto");
}

void ContactosPage::OnClickChoiseItem(wxCommandEvent& event) {
	cout << " Tocastess!!! " << choice->GetSelection() << endl;
	if (lastItemSelected != choice->GetSelection()) {
		lastItemSelected = choice->GetSelection();
		this->Reload();
	}

}

void ContactosPage::actionsHandler(int action) {
	switch (action) {
	case ACT_newContact: {
		PeopleContactCard* pop = new PeopleContactCard(lastItemSelected);
		pop->BuildPop(this);
		break;
	}
	case ACT_editContact: // Reenviar
		if (checkSelectedRowsNumber()) {
			wxArrayInt rows = this->grid->GetSelectedRows();
			this->curItem = this->grid->MygetRow(rows[0]);
			PeopleContactCard* pop = new PeopleContactCard(lastItemSelected);
			pop->BuildPop(this);
			pop->setValues(this->curItem);
		}
		break;
	case ACT_viewContact: // Responder
		if (checkSelectedRowsNumber()) {
			wxArrayInt rows = this->grid->GetSelectedRows();
			this->curItem = this->grid->MygetRow(rows[0]);
			PeopleContactCard* pop = new PeopleContactCard(lastItemSelected);
			pop->BuildPop(this);
			pop->setValues(this->curItem);
		}
		break;
	case ACT_deleteContact:
		if (checkSelectedRowsNumber()) {
			wxArrayInt rows = this->grid->GetSelectedRows();
			this->curItem = this->grid->MygetRow(rows[0]);

			map<string, string> *data = new map<string, string>;
			(*data)["noteID"] = this->curItem["ID"];
			Customcomunicate block = this->sendAction2(ACT_deleteContact, data);
			this->handleMessage(block);
		}
		break;

	case ACT_newPhone:
		break;
	case ACT_editPhone:
		break;
	case ACT_deletePhone:
		break;
	default:
		cout << "default" << endl;
		break;
	}

}

void ContactosPage::OnLeftDbClick(wxGridEvent& event) {
//	this->curAction = ACT_readMessage;
//	this->actionsHandler(this->curAction);
}

//void ContactosPage::replayAction(string action,map<string,string>data){
//	if ((action == "Reenviar") || (action == "Responder") ){
//		if (action == "Reenviar")
//			this->curAction = ACT_Forwards;
//		else
//			this->curAction = ACT_Replay;
//		this->curItem = data;
//		mensajeriaCard* pop = new mensajeriaCard;
//		pop->sendMode();
//		pop->BuildPop(this);
//		pop->setValues(this->curItem);
//	}
//	else{
////		this->filter = data;
////		Reload();
//		panelGrid::replayAction(action,data);
//	}
//}

void ContactosPage::buildQuery() {
// 	this->qry addField(string table, string field);
}

list<itemHeaderColumn> ContactosPage::headerGrid() {
	return getHeaderGrid();
}

list<itemHeaderColumn> ContactosPage::getHeaderGrid() {
	list<itemHeaderColumn> header;
	switch (lastItemSelected) {
	case type_Empresas:
		header.push_back(itemHeaderColumn("ID", "ID"));
		header.push_back(itemHeaderColumn("CIF", "CIF"));
		header.push_back(itemHeaderColumn("name", "name"));
		header.push_back(itemHeaderColumn("web", "web"));
		header.push_back(itemHeaderColumn("address", "address"));
		header.push_back(itemHeaderColumn("email", "email"));
		break;
	case type_Abogados:
		header.push_back(itemHeaderColumn("ID", "ID"));
		header.push_back(itemHeaderColumn("lawyerNumber", "lawyerNumber"));
		header.push_back(itemHeaderColumn("name", "name"));
		header.push_back(itemHeaderColumn("surnames", "surnames"));
		header.push_back(itemHeaderColumn("address", "address"));
		header.push_back(itemHeaderColumn("email", "email"));
		break;
	case type_Procuradores:
		header.push_back(itemHeaderColumn("ID", "ID"));
		header.push_back(itemHeaderColumn("attorneyNumber", "attorneyNumber"));
		header.push_back(itemHeaderColumn("name", "name"));
		header.push_back(itemHeaderColumn("surnames", "surnames"));
		header.push_back(itemHeaderColumn("address", "address"));
		header.push_back(itemHeaderColumn("email", "email"));
		break;
	case type_Clientes:
		header.push_back(itemHeaderColumn("ID", "ID"));
		header.push_back(itemHeaderColumn("DNI", "DNI"));
		header.push_back(itemHeaderColumn("name", "name"));
		header.push_back(itemHeaderColumn("surnames", "surnames"));
		header.push_back(itemHeaderColumn("address", "address"));
		header.push_back(itemHeaderColumn("email", "email"));
		break;

	}
	return header;
}

void ContactosPage::showList(Customcomunicate& block) {
	cout << "ContactosPage::ShowList" << endl;
	this->grid->pushDataSet(*block.dataset);
}

void ContactosPage::OnFilter() {
//	mensajeriaFilter* pop = new mensajeriaFilter;
//	pop->BuildPop(this);
//	pop->setValues(this->filter);
}

