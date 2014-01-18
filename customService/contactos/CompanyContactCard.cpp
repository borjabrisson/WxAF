// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "CompanyContactCard.h"



void CompanyContactCard::createAction(){
	this->AddComponent("receiver","Para",textInput,20,4);
	this->AddComponent("subject","Asunto",textInput,150);
	this->AddComponent("content","Mensaje",textAreaInput,600);
}



//void CompanyContactCard::HandleEvent(string action){
//	map<string,string> out = this->getInputsValue();
//	this->parent->replayAction(action,out);
//	this->Close(true);
//// 	this->Destroy();
//}

void CompanyContactCard::HandleEvent(string action){
	if ((action == "Salir")||(action == "Descartar")){
		this->Close(true);
		return;
	}
	else{
		if (checkInputsValue()){
				cout << "Dentro del IF HandleEvent!!!"<< endl;
				map<string,string> out = this->getInputsValue();
				this->parent->replayAction(action,out);
				this->Close(true);
			}
	}
}


void CompanyContactCard::readMode(){
	this->addAction("Responder");		this->addAction("Reenviar");		this->addAction("Salir");
}
void CompanyContactCard::sendMode(){
	this->addAction("Enviar");		this->addAction("Descartar");
}

// int CompanyContactCard::ChangeMode(bool lookup){
// 	map<string,string> out;
// 	out.insert(pair<string,string>("factura","1234"));
// 	out.insert(pair<string,string>("cliente","pepe"));
// 	this->setValues(out);
// 
// 	return 2;
// }

// list<row_type> CompanyContactCard::getLookupQuery(string action,map<string,string> &header){}

// void CompanyContactCard::setValues(map<string,string> values){
// 	if (this->lookup == "factura"){
// 		this->box->setValue("factura",values["factura"]);
// 	}
// }

