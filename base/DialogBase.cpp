// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "DialogBase.h"

DialogBase::DialogBase() :
		wxDialog() {

}
DialogBase::~DialogBase() {

}

int DialogBase::AddComponent(string id, string label, int type,int maxSize, int minSize, bool lookup) {
	itemCard item;
	if (!(textInput || timeInput || textAreaInput || dateInput || booleanInput|| optionInput))		return -1;

	item.type = type;		item.btn = NULL;			item.lookup = false;
	item.label = label;		item.minSize = minSize;		item.maxSize = maxSize;		item.lookup = lookup;

	this->inputs[id] = item;
	this->orderItem.push_back(id);

	return 0;
}

void DialogBase::OnLookUpBtn(wxCommandEvent& event){
	this->HandleLookupEvnt(this->lookupBtn[event.GetId()]);
}

void DialogBase::showMessage(string msg,string header){
	wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),wxString( header.c_str(), wxConvUTF8),   wxOK|wxICON_INFORMATION, this );
}

void DialogBase::addAction(string action){
	this->actions.push_back(action);
}
// int DialogBase::ChangeMode(bool lookup=false){return 0;}
// 
// void DialogBase::OnClick(wxCommandEvent& event){}
// 
// void DialogBase::HandleEvent(){}
