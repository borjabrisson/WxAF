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

int MyPopup::BuildPop(myPanel *parent){

// 	
// 	int widthBox , heightBox;
// 	this->box->GetSize(widthBox , heightBox);
	this->parent = parent;
	this->Create(parent, wxID_ANY,_T("Emergenteee"),wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
	
// 	this->box->BuildBox(this,widthBox , heightBox);	
// 	wxButton *btn = this->box->GetLookup("1");
// 	this->Connect(btn->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyPopup::OnClick) );
	
    this->box = new MyLookUpBox(this);
// 
	this->createAction();

	this->box->BuildBox();	

	this->box->SetParentEvent(this);

	int widthBox , heightBox;
	this->box->GetSize(widthBox , heightBox);
	this->SetSize(wxSize(widthBox,heightBox));
	
	this->Show();
// 	SetWindowStyle
	return 0;
}

int MyPopup::ChangeMode(bool lookup){

// 	if (lookup){
// 		this->SetSize(wxSize(500,500));
// 	}
// 	else{
// 		this->SetSize(wxSize(500,300));
// 	}

	int widthBox , heightBox;
	this->box->GetSize(widthBox , heightBox);
	this->SetSize(wxSize(widthBox,heightBox));
	
	this->Show();
// 	this->Refresh();
	return 0;
}

void MyPopup::HandleEvent(string action){
	map<string,string> out = this->box->getInputsValue();
	cout << "valor de los elementos "<< out["1"] << endl;
	this->parent->replayAction(action,out);
	this->Close(true);
// 	this->Destroy();
}


void MyPopup::OnClick(wxCommandEvent& event){
	string a = ""+event.GetId();
	cout << "Estoy ne el click"<<event.GetId() << endl;
// 	this->box->ChangeMode();
	new wxDialog(this,11,wxString( a.c_str(), wxConvUTF8),wxDefaultPosition,wxSize(300,300));
		wxMessageBox( _("wxWidgets Hello World example."), 
                  _("About Hello World"),
                  wxOK|wxICON_INFORMATION, this );
}


void MyPopup::createAction(){

	this->box->AddComponent("1","yeee",true);
	this->box->AddComponent("2","segundo");
	this->box->AddComponent("3","tercero");
	this->box->AddComponent("8","octavo",true);
}


void MyPopup::setValues(map<string,string> values){  //###: Lo hacemos así, o sería mejor usar la clase interna (lookupbox) ¿?
	map<string,string>::iterator it;

	for(it=values.begin();it!=values.end();it++){
		this->box->setValue((*it).first,(*it).second);
	}
	
}