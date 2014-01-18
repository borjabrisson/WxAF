// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "MensajeriaFilter.h"



void mensajeriaFilter::createAction(){
	this->AddComponent("sender","De",textInput,20);
	this->AddComponent("receiver","Para",textInput,20);

	this->AddComponent("subject","Asunto",textInput,150);
	this->AddComponent("content","Mensaje",textAreaInput,600);

	this->addAction("Guardar");		this->addAction("Salir");
}



//void mensajeriaFilter::HandleEvent(string action){
//	map<string,string> out = this->getInputsValue();
//	this->parent->replayAction(action,out);
//	this->Close(true);
//// 	this->Destroy();
//}

void mensajeriaFilter::HandleEvent(string action){
	if ((action == "Salir")||(action == "Descartar")){
		this->Close(true);
		return;
	}
	else{
		if (checkInputsValue()){
				map<string,string> out = this->getInputsValue();
				this->parent->replayAction(action,out);
				this->Close(true);
			}
	}
}

// list<row_type> mensajeriaFilter::getLookupQuery(string action,map<string,string> &header){}

// void mensajeriaFilter::setValues(map<string,string> values){
// 	if (this->lookup == "factura"){
// 		this->box->setValue("factura",values["factura"]);
// 	}
// }

