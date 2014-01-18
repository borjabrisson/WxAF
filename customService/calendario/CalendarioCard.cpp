// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "CalendarioCard.h"



void CalendarioCard::createAction(){

	//this->box->AddComponent("noteID","ID");
	this->AddComponent("dateNote","Fecha",dateInput);
	this->AddComponent("timeNote","hora",timeInput);
	this->AddComponent("description","Descripción",textAreaInput);

//	this->box->AddComponent("boool","bolll",booleanInput);
	this->AddComponent("daysToNotify","Dias para notificar");
	this->AddComponent("judProced","Procedimiento Asoc.");

	this->addAction("Aceptar");		this->addAction("Cancelar");
}



void CalendarioCard::HandleEvent(string action){
	if (action == "Cancelar"){
		this->Close(true);
		return;
	}
	else{
		MyPopup::HandleEvent(action);
	}
// 	this->Destroy();
}

// int CalendarioCard::ChangeMode(bool lookup){
// 	map<string,string> out;
// 	out.insert(pair<string,string>("factura","1234"));
// 	out.insert(pair<string,string>("cliente","pepe"));
// 	this->setValues(out);
// 
// 	return 2;
// }

// list<row_type> CalendarioCard::getLookupQuery(string action,map<string,string> &header){}

// void CalendarioCard::setValues(map<string,string> values){
// 	if (this->lookup == "factura"){
// 		this->box->setValue("factura",values["factura"]);
// 	}
// }

