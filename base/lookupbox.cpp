#include "lookupbox.h"

MyLookUpBox::MyLookUpBox(wxWindow *parent) : // Lo ideal seria tener una funcion para crear las acciones (botones) y un handler de sus clicks
		wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {
	this->labelSize = 100;
	this->InputSize = 100;
	this->heightRow = 30;
	this->btnActionSize = 100;

	this->mode = "card";
	this->parent = (DialogBase *) parent;

	mounthCode[1] = wxDateTime::Month::Jan;
	mounthCode[2] = wxDateTime::Month::Feb;
	mounthCode[3] = wxDateTime::Month::Mar;
	mounthCode[4] = wxDateTime::Month::Apr;
	mounthCode[5] = wxDateTime::Month::May;
	mounthCode[6] = wxDateTime::Month::Jun;

	mounthCode[7] = wxDateTime::Month::Jul;
	mounthCode[8] = wxDateTime::Month::Aug;
	mounthCode[9] = wxDateTime::Month::Sep;
	mounthCode[10] = wxDateTime::Month::Oct;
	mounthCode[11] = wxDateTime::Month::Nov;
	mounthCode[12] = wxDateTime::Month::Dec;

}

MyLookUpBox::~MyLookUpBox() { // Posiblemente no sea necesario su eliminacio, por lo que parece se borran solos.
}

int MyLookUpBox::ChangeMode() {

	if (this->mode == "lookup") {
		SetModeCard();
		return 1;
	}
	// Se encuentra en el modo card
	this->mode = "lookup";

	this->parent->ChangeMode(true);

	this->SetSizer(this->BagGrid, false);

	this->BagCard->ShowItems(false);
	this->BagGrid->ShowItems(true);

	this->BagGrid->Fit(this);
	this->BagGrid->SetSizeHints(this);

	return 2;

}

void MyLookUpBox::SetModeList() {

}

void MyLookUpBox::SetModeCard() {
	this->mode = "card";
	this->parent->ChangeMode(false);

	this->SetSizer(this->BagCard, false);

	this->BagGrid->ShowItems(false);
	this->BagCard->ShowItems(true);

	this->BagCard->Fit(this);
	this->BagCard->SetSizeHints(this);
}

int MyLookUpBox::BuildBox(map<string, itemCard> &inputs,
		map<int, string> &lookupBtn, list<string> &orderItem,
		list<string> &actions, int widthBox, int heightBox) {

	this->BuildCardBox(inputs, lookupBtn, orderItem, actions);
//	this->BuildListBox(widthBox, heightBox);

	//this->BagCard->ShowItems(true);
	if (this->mode == "card") {
		this->BagCard->ShowItems(true);
		this->parent->SetSize(this->BagCard->GetSize());
	} else {
		this->BagGrid->ShowItems(true);
		this->parent->SetSize(this->BagGrid->GetSize());
	}
	// asignamos el grid perteneciente al modo card y ocultamos los items del modo lista.
	return 0;
}

int MyLookUpBox::BuildCardBox(map<string, itemCard> &inputs,
		map<int, string> &lookupBtn, list<string> &orderItem,
		list<string> &actions) {
	this->BagCard = new wxGridBagSizer();

	this->SetSizer(this->BagCard); // ??

	this->BagCard->Add(this->InputSize / 2, 30, wxGBPosition(0, 0),
			wxGBSpan(1, 1), wxGROW);
	this->BagCard->Add(this->InputSize / 2, 30, wxGBPosition(0, 2),
			wxGBSpan(1, 1), wxGROW);

	itemCard item;
	list<string>::iterator it;
	int ind = 1;
	wxGridBagSizer *boxH; // = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *tag;
	wxButton* btn;
	for (it = orderItem.begin(); it != orderItem.end(); ind++, it++) {
		item = inputs[(*it)];
		item.input = createInputCard(item.type, item.maxSize);
		tag = createLabelInput(item.label);

		if (item.lookup) {
			btn = new wxButton(this, wxNewId(), _("#"), wxDefaultPosition,
					wxSize(this->heightRow, this->heightRow));
			lookupBtn[btn->GetId()] = (*it);
			item.btn = btn;
		} else {
			btn = NULL;
		}
		boxH = this->CreateCardRow(tag, item.input, btn);
		this->BagCard->Add(boxH, wxGBPosition(ind, 1), wxGBSpan(1, 1), wxGROW);
		inputs[(*it)] = item;
	}
	//this->BagCard->AddGrowableRow(0);
	// Creamos el area de las acciones.
	boxH = createSizerActions(actions);
	this->BagCard->Add(boxH, wxGBPosition(ind + 1, 1), wxGBSpan(1, 1), wxGROW);
	this->BagCard->Add(100, 30, wxGBPosition(ind + 2, 1), wxGBSpan(1, 1),
			wxGROW);

	this->BagCard->AddGrowableCol(1);

	this->BagCard->Fit(this);
	this->BagCard->SetSizeHints(this);
	return 0;
}

wxStaticText* MyLookUpBox::createLabelInput(string label) {
	return new wxStaticText(this, wxID_ANY, wxString(label.c_str(), wxConvUTF8),
			wxDefaultPosition, wxSize(this->labelSize, this->heightRow));
}

wxControl* MyLookUpBox::createInputCard(int type, int maxSize) {
	wxControl* input;
	switch (type) {
	case textInput:
	case timeInput:
		input = new wxTextCtrl(this, wxNewId(), _T(""), wxDefaultPosition,
				wxSize(this->InputSize, this->heightRow)); //,wxTE_PASSWORD);
		((wxTextCtrl*) input)->SetMaxLength(maxSize);
		break;
	case textAreaInput:
		input = new wxTextCtrl(this, wxNewId(), _T(""), wxDefaultPosition,
				wxSize(this->InputSize, this->heightRow * 7),
				wxHSCROLL | wxTE_MULTILINE); //,wxTE_PASSWORD);
		((wxTextCtrl*) input)->SetMaxLength(maxSize);
		break;
	case dateInput:
		input = new wxDatePickerCtrl(this, wxNewId(), wxDefaultDateTime,
				wxDefaultPosition, wxSize(this->InputSize, this->heightRow));
		break;
	case booleanInput:
		input = new wxCheckBox(this, wxNewId(),
				StdStringTowxString(((string)"")), wxDefaultPosition,
				wxSize(this->InputSize, this->heightRow), wxALIGN_RIGHT);
		break;
	case optionInput:
		break;
	default:
		push_Error("MyLookUpBox::AddComponent. Tipo de input inválido ");
		return NULL;
		break;
	}
	return input;
}

wxGridBagSizer* MyLookUpBox::CreateCardRow(wxStaticText* label,
		wxControl* input, wxButton* lookup) {

	wxGridBagSizer* boxH = new wxGridBagSizer();

	boxH->Add(label, wxGBPosition(0, 0), wxGBSpan(1, 1));
	boxH->Add(input, wxGBPosition(0, 1), wxGBSpan(1, 1), wxGROW);

	if (lookup != NULL) {
		boxH->Add(lookup, wxGBPosition(0, 2), wxGBSpan(1, 1));
		this->Connect(lookup->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
				wxCommandEventHandler(DialogBase::OnLookUpBtn));
	} else {
		boxH->Add(
				new wxStaticText(this, wxID_ANY, _(" "), wxDefaultPosition,
						wxSize(this->heightRow, this->heightRow)),
				wxGBPosition(0, 2), wxGBSpan(1, 1));
		// 			boxH->AddSpacer(10);
	}
	boxH->AddGrowableCol(1, 1);
	return boxH;
}

wxGridBagSizer* MyLookUpBox::createSizerActions(list<string> &actions) {
	list<string>::iterator it;
	int ind = 0;
	wxButton *btn;
	wxGridBagSizer *box = new wxGridBagSizer();
	for (it = actions.begin(); it != actions.end(); it++, ind++) {
		btn = new wxButton(this, wxNewId(), StdStringTowxString((*it)),
				wxDefaultPosition, wxSize(btnActionSize, heightRow));
		this->actionsEnable[btn->GetId()] = (*it);
		box->Add(btn, wxGBPosition(0, ind), wxGBSpan(1, 1), wxGROW);
		box->AddGrowableCol(ind);
		this->parent->Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(DialogBase::OnEventClick));
	}
	return box;
}

int MyLookUpBox::BuildListBox(int widthBox, int heightBox) {

	list<itemHeaderColumn> cols;

	this->BagGrid = new wxGridBagSizer();
	this->BagGrid->Fit(this); //this->BagGrid->SetSizeHints(this);
// 	this->SetSizer(this->BagGrid,false);

	this->grid = new MyGrid(this, wxID_ANY, cols); /*	this->grid->Show();*/

// 	this->grid = new wxGrid(this, wxID_ANY,wxDefaultPosition,wxDefaultSize);

	this->BagGrid->Add(this->grid, wxGBPosition(0, 0), wxGBSpan(3, 3), wxGROW);

	wxBoxSizer* boxH = new wxBoxSizer(wxHORIZONTAL);
	boxH->Add(
			new wxStaticText(this, wxID_ANY, _(" "), wxDefaultPosition,
					wxSize(200, this->heightRow)));

	//##! Sizer especifico para los botones de aceptar y cancelar
	/*boxH->Add(this->acept);
	 boxH->Add(
	 new wxStaticText(this, wxID_ANY, _(" "), wxDefaultPosition,
	 wxSize(this->heightRow, this->heightRow)));

	 boxH->Add(this->cancel);

	 this->BagGrid->Add(boxH, wxGBPosition(3, 1));*/
	this->BagGrid->AddGrowableRow(0);
	this->BagGrid->AddGrowableCol(2);

	this->BagGrid->ShowItems(false);

	return 0;
}

string MyLookUpBox::getValue(int type, wxControl *obj) {
	string value;
	switch (type) {
	case textInput:
	case textAreaInput: {
		wxString wxValue = ((wxTextCtrl *) obj)->GetValue();
		value = (const char*) wxValue.mb_str();
	}
		break;
	case dateInput: {
		wxDateTime date = ((wxDatePickerCtrl *) obj)->GetValue();
		value = date.FormatISODate().utf8_str();
	}
		break;
	case timeInput:
#ifdef wxVersion2_9
#endif
		break;
	case booleanInput:
	case optionInput:
		break;
	}
	return value;
}

void MyLookUpBox::setValue(int type, wxControl *obj, string value) {
	switch (type) {
	case textInput:
	case textAreaInput:
		((wxTextCtrl *) obj)->SetValue(
				StdStringTowxString(value));
		break;
	case dateInput: {
		wxDateTime date;
		if (date.ParseDate(StdStringTowxString(value))) {
			int day, month, year, prevSeparator, nextSeparator = value.find("-");

			year = atoi(value.substr(0, nextSeparator).c_str());
			prevSeparator = nextSeparator;
			nextSeparator = value.find("-", prevSeparator + 1);

			month = atoi(
					value.substr(prevSeparator + 1,
							nextSeparator - (prevSeparator + 1)).c_str());
			day = atoi(value.substr(nextSeparator + 1).c_str());
			// Debido a fallos/deficiiencias en la libreria WxWidgets1.8 nos vemos obligados a usar esta alternativa
			date.SetDay(day);
			date.SetMonth(mounthCode[month]);
			date.SetYear(year);
			((wxDatePickerCtrl *) obj)->SetValue(date); //wxDateTime(day,month,year));
		} else
			push_Error(
					" MyLookUpBox::setValue. Valor incorrecto para DateTime: "
							+ value);
	}
		break;
	case timeInput:
#ifdef wxVersion2_9
#endif
		break;
	case booleanInput:
	case optionInput:
		break;
	}
	return;
}

string MyLookUpBox::getActionsID(int btnID){
	return this->actionsEnable[btnID];
}
