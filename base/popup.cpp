// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "popup.h"

MyPopup::MyPopup():DialogBase(){
// 	this->box = new MyLookUpBox;

}
MyPopup::~MyPopup(){
// // 		delete this->grid;
// delete this->text;
}

int MyPopup::BuildPop(myPanel *parent,string tittle){

// 	
// 	int widthBox , heightBox;
// 	this->box->GetSize(widthBox , heightBox);
	this->parent = parent;
	this->Create(parent, wxNewId(),StdStringTowxString(tittle),wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

    this->box = new MyLookUpBox(this);
	this->createAction();
	this->box->BuildBox(inputs,lookupBtn,orderItem,actions);

//	this->SetSize(wxSize(500,500));
//	this->box->BagCard->Fit(this);
//	this->box->BagCard->SetSizeHints(this);

// 	SetWindowStyle
//	this->Login();
	this->Show();
	return 0;
}

/*
void MyPopup::Login(){
	int inputSize =100, heightRow=30;
	int xBase=50, yBase=15;
	wxBoxSizer *boxH,*boxV;
	wxGridBagSizer *BagCard = new wxGridBagSizer();
	wxStaticText *text;
	wxTextCtrl *input;
	wxButton *btn;

	text = new wxStaticText (this, wxNewId(), _(" "), wxDefaultPosition, wxSize(3,heightRow));

	BagCard->Add(text, wxGBPosition(0, 0), wxGBSpan(1, 1),wxGROW);
	BagCard->Add(text, wxGBPosition(0, 2), wxGBSpan(1, 1),wxGROW);

	boxH = new wxBoxSizer(wxHORIZONTAL);

	boxH->Add(new wxStaticText (this, wxNewId(), _("Usuario: "), wxDefaultPosition, wxSize(inputSize,heightRow)), wxSizerFlags().Expand());
	boxH->Add(new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(inputSize,heightRow)), wxSizerFlags().Expand());

	BagCard->Add(boxH, wxGBPosition(1, 1), wxGBSpan(1, 1), wxGROW);

	boxH = new wxBoxSizer(wxHORIZONTAL);
	boxH->Add(new wxStaticText (this, wxNewId(), _("Contraseña: "),wxDefaultPosition, wxSize(inputSize,heightRow)));
	boxH->Add(new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(inputSize,heightRow),wxTE_PASSWORD));

	BagCard->Add(boxH, wxGBPosition(2, 1), wxGBSpan(1, 1), wxGROW);

	boxH = new wxBoxSizer(wxHORIZONTAL);
	boxH->Add(new wxButton(this, wxNewId(), _("Aceptar"), wxDefaultPosition,  wxSize(inputSize,heightRow)));
	boxH->Add(new wxButton(this, wxNewId(), _("Cancelar"), wxDefaultPosition,  wxSize(inputSize,heightRow)));

	BagCard->Add(boxH, wxGBPosition(3, 1), wxGBSpan(1, 1), wxGROW);
	SetSizer(BagCard);

	BagCard->AddGrowableRow(1); BagCard->AddGrowableCol(1);
	BagCard->AddGrowableRow(2); BagCard->AddGrowableCol(2);
	BagCard->Fit(this);
	BagCard->SetSizeHints(this);
	this->Show();
}*/

/*void MyPopup::Login(){
	int inputSize =100, heightRow=30;
	int xBase=50, yBase=15;
	wxBoxSizer *boxH,*boxV;
	wxGridBagSizer *BagCard = new wxGridBagSizer();
	wxStaticText *text;
	wxTextCtrl *input;
	wxButton *btn;

	text = new wxStaticText (this, wxNewId(), _(" "), wxDefaultPosition, wxSize(3,heightRow));

	BagCard->Add(text, wxGBPosition(0, 0), wxGBSpan(1, 1),wxGROW);
	BagCard->Add(text, wxGBPosition(0, 3), wxGBSpan(1, 1),wxGROW);


	text = new wxStaticText (this, wxNewId(), _("Usuario: "), wxDefaultPosition, wxSize(inputSize,heightRow));
	BagCard->Add(text, wxGBPosition(1, 1), wxGBSpan(1, 1), wxGROW);

	input = new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(inputSize,heightRow));
	BagCard->Add(input, wxGBPosition(1, 2), wxGBSpan(1, 1), wxGROW);


	text = new wxStaticText (this, wxNewId(), _("Contraseña: "),wxDefaultPosition, wxSize(inputSize,heightRow));
	BagCard->Add(text, wxGBPosition(2, 1), wxGBSpan(1, 1), wxGROW);

	input = new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(inputSize,heightRow),wxTE_PASSWORD);
	BagCard->Add(input, wxGBPosition(2, 2), wxGBSpan(1, 1), wxGROW);


	btn = new wxButton(this, wxNewId(), _("Aceptar"), wxDefaultPosition,  wxSize(inputSize,heightRow));
	BagCard->Add(btn, wxGBPosition(3, 1), wxGBSpan(1, 1), wxGROW);

	btn = new wxButton(this, wxNewId(), _("Cancelar"), wxDefaultPosition,  wxSize(inputSize,heightRow));
	BagCard->Add(btn, wxGBPosition(3, 2), wxGBSpan(1, 1), wxGROW);

	SetSizer(BagCard);

//	BagCard->AddGrowableRow(1,1);
	BagCard->AddGrowableCol(1,1);
//	BagCard->AddGrowableRow(2,1);
	BagCard->AddGrowableCol(2,1);
	BagCard->Fit(this);
	BagCard->SetSizeHints(this);
	this->Show();
}*/

/*
void MyPopup::Login(){
	int inputSize =100, heightRow=30;
	int xBase=50, yBase=15;
	wxGridBagSizer *boxH,*boxV;
	wxGridBagSizer *BagCard = new wxGridBagSizer();
	wxStaticText *text;
	wxTextCtrl *input;
	wxButton *btn;

	text = new wxStaticText (this, wxNewId(), _(" "), wxDefaultPosition, wxSize(3,heightRow));

	BagCard->Add(text, wxGBPosition(0, 0), wxGBSpan(1, 1));
	BagCard->Add(text, wxGBPosition(0, 2), wxGBSpan(1, 1));

	boxH = new wxGridBagSizer();
	boxH->Add(new wxStaticText (this, wxNewId(), _("Usuario: "), wxDefaultPosition, wxSize(inputSize,heightRow)),  wxGBPosition(0, 0), wxGBSpan(1, 1)  );
	boxH->Add(new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(inputSize,heightRow)), wxGBPosition(0, 1), wxGBSpan(1, 1),wxGROW );

	boxH->AddGrowableCol(1,1);
	BagCard->Add(boxH, wxGBPosition(1, 1), wxGBSpan(1, 1), wxGROW);

	boxH = new wxGridBagSizer();
	boxH->Add(new wxStaticText (this, wxNewId(), _("Contraseña: "), wxDefaultPosition, wxSize(inputSize,heightRow)),  wxGBPosition(0, 0), wxGBSpan(1, 1)  );
	boxH->Add(new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(inputSize,heightRow),wxTE_PASSWORD), wxGBPosition(0, 1), wxGBSpan(1, 1),wxGROW );

	boxH->AddGrowableCol(1,1);

	BagCard->Add(boxH, wxGBPosition(2, 1), wxGBSpan(1, 1), wxGROW);


	boxH = new wxGridBagSizer();
	boxH->Add(new wxButton(this, wxNewId(), _("Aceptar"), wxDefaultPosition,  wxSize(inputSize,heightRow)),wxGBPosition(0, 0), wxGBSpan(1, 1),wxGROW );
	boxH->Add(new wxButton(this, wxNewId(), _("Cancelar"), wxDefaultPosition,  wxSize(inputSize,heightRow)),wxGBPosition(0, 1), wxGBSpan(1, 1),wxGROW );
	boxH->Add(new wxButton(this, wxNewId(), _("Otro"), wxDefaultPosition,  wxSize(inputSize,heightRow)),wxGBPosition(0, 2), wxGBSpan(1, 1),wxGROW );

	boxH->AddGrowableCol(0,1);	boxH->AddGrowableCol(1,1); boxH->AddGrowableCol(2,1);
	BagCard->Add(boxH, wxGBPosition(3, 1), wxGBSpan(1, 1), wxGROW);

	SetSizer(BagCard);

	BagCard->AddGrowableCol(1,1);	//BagCard->AddGrowableCol(2,1);
	BagCard->Fit(this);
	BagCard->SetSizeHints(this);
	this->Show();
}
*/
void MyPopup::Login(){

	int inputSize =100, heightRow=30;
	int xBase=50, yBase=15;

	//new wxStaticText (this, wxNewId(), _("Usuario: "), wxPoint(xBase,yBase), wxSize(inputSize,heightRow));
	new wxStaticText (this, wxNewId(), _("Contraseña: "),wxPoint(xBase,yBase+heightRow), wxSize(inputSize,heightRow));


//	wxTextCtrl *btn = new wxTextCtrl(this,wxNewId(),_T(""),wxPoint(xBase+inputSize,yBase), wxSize(inputSize,heightRow));
//	btn->SetHint(_T("Hola"));
	new wxTextCtrl(this,wxNewId(),_T(""),wxPoint(xBase+inputSize,yBase+heightRow), wxSize(inputSize,heightRow),wxTE_PASSWORD);

	new wxButton(this, wxNewId(), _("Aceptar"), wxPoint(xBase,yBase+2*heightRow),  wxSize(inputSize,heightRow));
	new wxButton(this, wxNewId(), _("Cancelar"), wxPoint(xBase+inputSize,yBase+2*heightRow),  wxSize(inputSize,heightRow));

}
int MyPopup::ChangeMode(bool lookup){

//	int widthBox , heightBox;
//	this->box->GetSize(widthBox , heightBox);
//	this->SetSize(wxSize(widthBox,heightBox));

	this->Show();
// 	this->Refresh();
	return 0;
}

void MyPopup::HandleEvent(string action){
	if (checkInputsValue()){
		map<string,string> out = this->getInputsValue();
		this->parent->replayAction(action,out);
		this->Close(true);
	}
// 	this->Destroy();
}

void MyPopup::createAction(){

	this->AddComponent("1","yeee",true);
	this->AddComponent("2","segundo");
	this->AddComponent("3","tercero");
	this->AddComponent("8","octavo",true);
}

map<string,string> MyPopup::getInputsValue(){
	map<string, itemCard>::iterator it;
	itemCard item;
	for(it = inputs.begin(); it != inputs.end(); it++){
		item = (*it).second;
		this->curRecord[(*it).first] = box->getValue(item.type,item.input);
	}
	return this->curRecord;
}

bool MyPopup::checkInputsValue(){
	map<string, itemCard>::iterator it;
	itemCard item;
	string value;
	int size;
	for(it = inputs.begin(); it != inputs.end(); it++){
		item = (*it).second;
		value = box->getValue(item.type,item.input);
		size = value.length();
		if (size < item.minSize){
			showMessage("El campo "+ item.label + " es demasiado pequeño");
			return false;
		}

		if ((size > item.maxSize) && (item.maxSize != -1)){
			showMessage("El campo "+ item.label + " es demasiado grande");
			return false;
		}
	}
	return true;
}

void MyPopup::setValues(map<string,string> values){  //###: Lo hacemos así, o sería mejor usar la clase interna (lookupbox) ¿?
	map<string,string>::iterator it;
	itemCard item;
	for(it=values.begin();it!=values.end();it++){
		if (this->inputs.count((*it).first)){
			item = this->inputs[(*it).first];
			box->setValue(item.type,item.input,(*it).second);
		}
	}
	this->curRecord = values;
}

void MyPopup::OnEventClick(wxCommandEvent& event){
	string action = box->getActionsID(event.GetId());
	this->HandleEvent(action);
}
